use std::{fs, process::exit};

mod asm_gen;
mod code_emission;
mod lexer;
mod parser;
mod queue;
mod tac;

use clap::Parser;

use crate::{
    asm_gen::gen_asm,
    code_emission::{assemble_and_link, emit_assembly},
    lexer::lex_string,
    parser::parse,
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

    filename: String,
}

fn asm_output_name(input: &str) -> String {
    if let Some(pos) = input.rfind('.') {
        format!("{}.s", &input[..pos])
    } else {
        format!("{}.s", input)
    }
}

fn exe_output_name(input: &str) -> String {
    if let Some(pos) = input.rfind('.') {
        input[..pos].to_string()
    } else {
        input.to_string()
    }
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

    let program = parse(lexeme);
    println!("AST:\n{:#?}", program);
    if args.parse {
        return;
    }

    let asm_ast = gen_asm(program);
    println!("ASM-AST:\n{:#?}", asm_ast);
    if args.codegen {
        return;
    }

    let asm_text = emit_assembly(&asm_ast);

    let output_file = asm_output_name(&args.filename);

    fs::write(&output_file, asm_text).unwrap_or_else(|_| {
        eprintln!("Failed to write assembly output");
        exit(1);
    });

    println!("Assembly written to {}", output_file);

    let exe_file = exe_output_name(&args.filename);

    assemble_and_link(&output_file, &exe_file);

    println!("Executable written to {}", exe_file);
}
