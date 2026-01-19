use std::{
    fs,
    io::Write,
    os::unix::process::ExitStatusExt,
    path::Path,
    process::{Command, exit},
};

mod ast;
mod gen_names;
mod lexer;
mod llvm_codegen;
mod parser;
mod queue;
mod semantic;
mod tac;
mod utils;

use clap::Parser;

use crate::{
    lexer::lex_string, llvm_codegen::emit_llvm, parser::parse, semantic::semantic_analysis,
    tac::gen_tac,
};

static mut VERBOSE: bool = false;

macro_rules! vprintln {
    ($($arg:tt)*) => {
        unsafe {
            if VERBOSE {
                println!($($arg)*);
            }
        }
    }
}

#[derive(Parser, Debug)]
#[command(author, version, about)]
struct Args {
    #[arg(long)]
    lex: bool,

    #[arg(long)]
    parse: bool,

    #[arg(long)]
    codegen: bool,

    #[arg(long)]
    tacky: bool,

    #[arg(long)]
    validate: bool,

    #[arg(short)]
    c: bool,

    #[arg(short, long)]
    verbose: bool,

    filename: String,
}
use std::process::Stdio;

pub fn compile_ir(input_path: &str, asm_text: &str, object_only: bool) -> String {
    let input_path = Path::new(input_path);
    let build_dir = input_path
        .parent()
        .unwrap_or_else(|| Path::new("."))
        .join("build");

    if let Err(e) = std::fs::create_dir_all(&build_dir) {
        eprintln!("Failed to create build directory '{:?}': {}", build_dir, e);
        std::process::exit(1);
    }

    let llvm_file = build_dir
        .join(input_path.file_stem().unwrap())
        .with_extension("ll");

    let file = build_dir.join(input_path.file_stem().unwrap());

    let output_file = if object_only {
        file.with_extension(".o").to_string_lossy().to_string()
    } else {
        file.with_extension("").to_string_lossy().to_string()
    };

    if let Err(e) = std::fs::write(&llvm_file, asm_text) {
        vprintln!("Failed to write LLVM IR to '{:?}': {}", llvm_file, e);
        std::process::exit(1);
    }
    vprintln!("LLVM IR written to '{:?}'", llvm_file);

    let mut cmd = Command::new("cc");
    cmd.arg(&llvm_file).stderr(Stdio::piped());
    if object_only {
        cmd.arg("-c");
    }
    cmd.arg("-o").arg(&output_file);

    let status = cmd.status().unwrap_or_else(|e| {
        vprintln!("Failed to invoke compiler: {}", e);
        std::process::exit(1);
    });

    if !status.success() {
        vprintln!("Compilation failed with status: {}", status);
        std::process::exit(1);
    }

    vprintln!("Output written to '{}'", output_file);
    output_file
}

fn main() {
    let args = Args::parse();

    unsafe {
        VERBOSE = args.verbose;
    }

    let content = fs::read_to_string(&args.filename).expect("Failed to read the input file");

    vprintln!("Processing file: {}", args.filename);

    let lexeme = lex_string(content);
    vprintln!("Lexeme: {:?}", lexeme);
    if args.lex {
        return;
    }

    let ast = parse(lexeme);
    vprintln!("AST:\n{:#?}", ast);
    if args.parse {
        return;
    }

    let transformed_ast = semantic_analysis(ast);
    vprintln!("AST after Semantic Analysis:\n{:#?}", transformed_ast);
    if args.validate {
        return;
    }

    let tac_ast = gen_tac(transformed_ast);
    vprintln!("TAC-AST:\n{:#?}", tac_ast);
    if args.tacky {
        return;
    }

    let llvm_ir = emit_llvm(&tac_ast);
    vprintln!("LLVM IR:\n{}", llvm_ir);
    if args.codegen {
        return;
    }

    let output_file = compile_ir(&args.filename, &llvm_ir, args.c);

    if !args.c {
        vprintln!("Running executable...");
        let output = std::process::Command::new(&output_file)
            .output()
            .expect("Failed to execute program");
        
        std::io::stdout().write_all(&output.stdout).unwrap();
        std::io::stderr().write_all(&output.stderr).unwrap();

        std::process::exit(output.status.code().unwrap_or(1));
    }
}
