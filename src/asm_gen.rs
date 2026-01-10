use clap::Id;

use crate::{
    parser::{Expr, FuncDef, Program, Stmt},
    tac::{TacBinaryOp, TacFuncDef, TacInstruction, TacProgram, TacUnaryOp, TacVal},
};
use std::{collections::HashMap, fmt::Write};

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
    Unary(AsmUnaryOp, AsmOperand),
    Binary(AsmBinaryOp, AsmOperand, AsmOperand),
    Idiv(AsmOperand),
    Cdq,
    AllocateStack(i32),
    Ret,
}
#[derive(Debug, Clone)]
pub enum AsmUnaryOp {
    Neg,
    Not,
}
#[derive(Debug)]
pub enum AsmBinaryOp {
    Add,
    Subtract,
    Multiply,
}
#[derive(Debug, Clone)]
pub enum AsmOperand {
    Imm(i32),
    Reg(AsmReg),
    Pseudo(String),
    Stack(i32),
}
#[derive(Debug, Clone)]
pub enum AsmReg {
    Ax,
    R10,
}

pub fn gen_asm(program: TacProgram) -> AsmProgram {
    match program {
        TacProgram::Program { main_func } => {
            let asm_func = convert_func(main_func);

            let (asm_func, stack_size) = replace_pseudoregisters(asm_func);

            let asm_func = fixup_instructions(asm_func, stack_size);

            AsmProgram::Program(asm_func)
        }
    }
}

fn replace_pseudoregisters(func: AsmFuncDef) -> (AsmFuncDef, i32) {
    let AsmFuncDef::Function { name, instructions } = func;

    let mut offsets: HashMap<String, i32> = HashMap::new();
    let mut next_offset: i32 = -16;

    fn replace_op(
        op: AsmOperand,
        offsets: &mut HashMap<String, i32>,
        next_offset: &mut i32,
    ) -> AsmOperand {
        match op {
            AsmOperand::Pseudo(name) => {
                let offset = offsets.entry(name).or_insert_with(|| {
                    let off = *next_offset;
                    *next_offset -= 4;
                    off
                });
                AsmOperand::Stack(*offset)
            }
            other => other,
        }
    }

    let new_instructions = instructions
        .into_iter()
        .map(|instr| match instr {
            AsmInstruction::Mov { src, dest } => AsmInstruction::Mov {
                src: replace_op(src, &mut offsets, &mut next_offset),
                dest: replace_op(dest, &mut offsets, &mut next_offset),
            },

            AsmInstruction::Unary(op, operand) => {
                AsmInstruction::Unary(op, replace_op(operand, &mut offsets, &mut next_offset))
            }

            AsmInstruction::Binary(op, src, dest) => AsmInstruction::Binary(
                op,
                replace_op(src, &mut offsets, &mut next_offset),
                replace_op(dest, &mut offsets, &mut next_offset),
            ),

            AsmInstruction::Idiv(op) => {
                AsmInstruction::Idiv(replace_op(op, &mut offsets, &mut next_offset))
            }

            other => other,
        })
        .collect();

    let stack_size = ((-next_offset + 15) / 16) * 16;

    (
        AsmFuncDef::Function {
            name,
            instructions: new_instructions,
        },
        stack_size,
    )
}

fn fixup_instructions(func: AsmFuncDef, stack_size: i32) -> AsmFuncDef {
    let AsmFuncDef::Function { name, instructions } = func;

    let mut fixed = Vec::new();

    if stack_size > 0 {
        fixed.push(AsmInstruction::AllocateStack(stack_size));
    }

    for instr in instructions {
        match instr {
            AsmInstruction::Mov {
                src: src @ AsmOperand::Stack(_),
                dest: dest @ AsmOperand::Stack(_),
            } => {
                fixed.push(AsmInstruction::Mov {
                    src: AsmOperand::Reg(AsmReg::R10),
                    dest: dest.clone(),
                });
                fixed.push(AsmInstruction::Mov {
                    src,
                    dest: AsmOperand::Reg(AsmReg::R10),
                });
            }
            other => fixed.push(other),
        }
    }

    AsmFuncDef::Function {
        name,
        instructions: fixed,
    }
}

fn convert_func(func: TacFuncDef) -> AsmFuncDef {
    match func {
        TacFuncDef::Function { name, body } => {
            let mut instructions = Vec::new();

            convert_instr(body, &mut instructions);

            AsmFuncDef::Function { name, instructions }
        }
    }
}

fn convert_instr(tac_instructions: Vec<TacInstruction>, instructions: &mut Vec<AsmInstruction>) {
    use AsmInstruction::*;
    for instr in tac_instructions {
        let mut new_instr = match instr {
            TacInstruction::Return(val) => vec![
                Mov {
                    src: tac_op_to_asm(val),
                    dest: AsmOperand::Reg(AsmReg::Ax),
                },
                Ret,
            ],
            TacInstruction::Unary { op, src, dest } => {
                let asm_dest = tac_op_to_asm(dest);
                vec![
                    Mov {
                        src: tac_op_to_asm(src),
                        dest: asm_dest.clone(),
                    },
                    Unary(tac_unop_to_asm(op), asm_dest),
                ]
            }
            TacInstruction::Binary {
                op,
                src1,
                src2,
                dest,
            } => {
                let asm_src1 = tac_op_to_asm(src1);
                let asm_src2 = tac_op_to_asm(src2);
                let asm_dest = tac_op_to_asm(dest);
                if matches!(
                    op,
                    TacBinaryOp::Multiply | TacBinaryOp::Add | TacBinaryOp::Subtract
                ) {
                    let asm_op = tac_binop_to_asm(op);

                    vec![
                        Mov {
                            src: asm_src1,
                            dest: asm_dest.clone(),
                        },
                        Binary(asm_op, asm_src2, asm_dest),
                    ]
                } else {
                    vec![
                        Mov {
                            src: asm_src1,
                            dest: AsmOperand::Reg(AsmReg::Ax),
                        },
                        Cdq,
                        Idiv(asm_src2),
                        Mov {
                            src: AsmOperand::Reg(AsmReg::Ax),
                            dest: asm_dest,
                        },
                    ]
                }
            }
        };
        instructions.append(&mut new_instr);
    }
}

fn tac_op_to_asm(input: TacVal) -> AsmOperand {
    use AsmOperand::{Imm, Pseudo};
    match input {
        TacVal::Constant(int) => Imm(int),
        TacVal::Var(ident) => Pseudo(ident),
    }
}

fn tac_unop_to_asm(input: TacUnaryOp) -> AsmUnaryOp {
    use AsmUnaryOp::*;
    use TacUnaryOp::*;
    match input {
        Complement => Not,
        Negate => Neg,
    }
}
fn tac_binop_to_asm(op: TacBinaryOp) -> AsmBinaryOp {
    use AsmBinaryOp::*;
    match op {
        TacBinaryOp::Add => Add,
        TacBinaryOp::Subtract => Subtract,
        TacBinaryOp::Multiply => Multiply,
        _ => unimplemented!(),
    }
}
