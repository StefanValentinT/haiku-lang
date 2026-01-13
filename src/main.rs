use std::{
    fs,
    process::{Command, exit},
};

mod asm_gen;
mod code_emission;
mod lexer;
mod parser;
mod queue;
mod semantic;
mod tac;
mod utils;
use clap::Parser;

use crate::{
    asm_gen::gen_asm, code_emission::*, lexer::lex_string, parser::parse,
    semantic::semantic_analysis, tac::gen_tac,
};

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

    filename: String,
}

pub fn compile_assembly(input_path: &str, asm_text: &str, object_only: bool) -> String {
    let asm_file = if let Some(pos) = input_path.rfind('.') {
        format!("{}.s", &input_path[..pos])
    } else {
        format!("{}.s", input_path)
    };

    let output_file = if object_only {
        if let Some(pos) = input_path.rfind('.') {
            format!("{}.o", &input_path[..pos])
        } else {
            format!("{}.o", input_path)
        }
    } else {
        if let Some(pos) = input_path.rfind('.') {
            input_path[..pos].to_string()
        } else {
            input_path.to_string()
        }
    };

    fs::write(&asm_file, asm_text).unwrap_or_else(|_| {
        eprintln!("Failed to write assembly file: {}", asm_file);
        exit(1);
    });
    println!("Assembly written to {}", asm_file);

    let mut cmd = Command::new("cc");
    cmd.arg(&asm_file);

    if object_only {
        cmd.arg("-c");
    } else {
        cmd.arg("-o").arg(&output_file);
    }

    let status = cmd.status().expect("Failed to invoke system compiler");
    if !status.success() {
        eprintln!("Compilation failed");
        exit(1);
    }

    println!("Output written to {}", output_file);

    output_file
}

fn main() {
    let args = Args::parse();

    let content = fs::read_to_string(&args.filename).expect("Failed to read the input file");

    println!("Processing file: {}", args.filename);

    let lexeme = lex_string(content);
    println!("Lexeme: {:?}", lexeme);
    if args.lex {
        return;
    }

    let ast = parse(lexeme);
    println!("AST:\n{:#?}", ast);
    if args.parse {
        return;
    }

    let transformed_ast = semantic_analysis(ast);
    println!("AST after Semantic Analysis:\n{:#?}", transformed_ast);
    if args.validate {
        return;
    }

    let tac_ast = gen_tac(transformed_ast);
    println!("TAC-AST:\n{:#?}", tac_ast);
    if args.tacky {
        return;
    }

    let asm_ast = gen_asm(tac_ast);
    println!("ASM-AST:\n{:#?}", asm_ast);
    if args.codegen {
        return;
    }

    let asm = emit_assembly(&asm_ast);
    println!("Assembly:\n{:#?}", asm);

    let output_file = compile_assembly(&args.filename, &asm, args.c);

    if !args.c {
        println!("Running executable...");
        let status = Command::new(&output_file)
            .status()
            .expect("Failed to execute program");

        match status.code() {
            Some(code) => println!("Program result: {}", code as i8),
            None => println!("Program terminated by signal"),
        }
    }
}
