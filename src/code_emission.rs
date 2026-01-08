use crate::asm_gen::*;
use std::{
    fmt::Write,
    process::{Command, exit},
};

pub fn emit_assembly(program: &AsmProgram) -> String {
    let mut output = String::new();

    match program {
        AsmProgram::Program(func) => emit_function(func, &mut output),
    }

    output
}

fn emit_function(func: &AsmFuncDef, out: &mut String) {
    let AsmFuncDef::Function { name, instructions } = func;

    // macOS uses underscore-prefixed symbols
    let asm_name = if cfg!(target_os = "macos") {
        format!("_{}", name)
    } else {
        name.clone()
    };

    writeln!(out, ".globl {}", asm_name).unwrap();
    writeln!(out, "{}:", asm_name).unwrap();

    for instr in instructions {
        emit_instruction(instr, out);
    }
}

fn emit_instruction(instr: &AsmInstruction, out: &mut String) {
    match instr {
        AsmInstruction::Mov { src, dest } => {
            write!(out, "    mov ").unwrap();
            emit_operand(dest, out);
            write!(out, ", ").unwrap();
            emit_operand(src, out);
            writeln!(out).unwrap();
        }

        AsmInstruction::Ret => {
            writeln!(out, "    ret").unwrap();
        }
    }
}

fn emit_operand(op: &AsmOperand, out: &mut String) {
    match op {
        // AArch64 return register (32-bit int)
        AsmOperand::Register => {
            write!(out, "w0").unwrap();
        }

        AsmOperand::Imm(val) => {
            write!(out, "#{}", val).unwrap();
        }
    }
}

pub fn assemble_and_link(asm_file: &str, exe_file: &str) {
    let mut cmd = Command::new("cc");

    cmd.arg(asm_file).arg("-o").arg(exe_file);

    let status = cmd.status().expect("Failed to invoke system compiler");

    if !status.success() {
        eprintln!("Assembler/linker failed");
        exit(1);
    }
}
