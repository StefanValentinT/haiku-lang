use crate::parser::{Expr, FuncDef, Program, Stmt};
use std::fmt::Write;

#[derive(Debug)]
pub enum AsmProgram {
    Program(AsmFuncDef),
}
#[derive(Debug)]
pub enum AsmFuncDef {
    Function {
        name: String,
        instructions: Vec<AsmInstruction>,
    },
}
#[derive(Debug)]
pub enum AsmInstruction {
    Mov { src: AsmOperand, dest: AsmOperand },
    Ret,
}
#[derive(Debug)]
pub enum AsmOperand {
    Imm(i32),
    Register,
}

pub fn gen_asm(program: Program) -> AsmProgram {
    match program {
        Program::Program { main_func } => {
            let asm_func = convert_func(main_func);
            AsmProgram::Program(asm_func)
        }
    }
}

fn convert_func(func: FuncDef) -> AsmFuncDef {
    match func {
        FuncDef::Function { name, body } => {
            let mut instructions = Vec::new();

            convert_stmt(body, &mut instructions);

            AsmFuncDef::Function { name, instructions }
        }
    }
}

fn convert_stmt(stmt: Stmt, instructions: &mut Vec<AsmInstruction>) {
    match stmt {
        Stmt::Return(expr) => {
            let operand = convert_expr(expr, instructions);

            instructions.push(AsmInstruction::Mov {
                src: operand,
                dest: AsmOperand::Register,
            });

            instructions.push(AsmInstruction::Ret);
        }
    }
}

fn convert_expr(expr: Expr, _instructions: &mut Vec<AsmInstruction>) -> AsmOperand {
    match expr {
        Expr::Constant(val) => AsmOperand::Imm(val),
        Expr::Unary(op, expr) => todo!(),
    }
}
