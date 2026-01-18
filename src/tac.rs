use crate::ast::ast_type::*;
use crate::ast::typed_ast::*;
use crate::gen_names::*;

#[derive(Debug)]
pub enum TacProgram {
    Program(Vec<TacFuncDef>),
}

#[derive(Debug)]
pub enum TacFuncDef {
    Function {
        name: String,
        params: Vec<String>,
        ret_type: Type,
        body: Vec<TacInstruction>,
    },
}

#[derive(Debug)]
pub enum TacInstruction {
    Return(TacVal),
    Truncate {
        src: TacVal,
        dest: TacVal,
    },
    SignExtend {
        src: TacVal,
        dest: TacVal,
    },
    Unary {
        op: TacUnaryOp,
        src: TacVal,
        dest: TacVal,
    },
    Binary {
        op: TacBinaryOp,
        src1: TacVal,
        src2: TacVal,
        dest: TacVal,
    },
    Copy {
        src: TacVal,
        dest: TacVal,
    },
    Jump {
        target: String,
    },
    JumpIfZero {
        condition: TacVal,
        target: String,
    },
    JumpIfNotZero {
        condition: TacVal,
        target: String,
    },
    Label(String),
    FunCall {
        fun_name: String,
        args: Vec<TacVal>,
        dest: TacVal,
    },
}

#[derive(Debug, Clone)]
pub enum TacVal {
    I32(i32),
    I64(i64),
    Var(String, Type),
}

#[derive(Debug, PartialEq)]
pub enum TacUnaryOp {
    Complement,
    Negate,
    Not,
}

#[derive(Debug)]
pub enum TacBinaryOp {
    Add,
    Subtract,
    Multiply,
    Divide,
    Remainder,
    Equal,
    NotEqual,
    LessThan,
    LessOrEqual,
    GreaterThan,
    GreaterOrEqual,
}

pub fn gen_tac(program: TypedProgram) -> TacProgram {
    let tac_funcs = program.functions.into_iter().map(func_to_tac).collect();
    TacProgram::Program(tac_funcs)
}

fn func_to_tac(func: TypedFunDecl) -> TacFuncDef {
    let mut instructions = Vec::new();
    let has_body = func.body.is_some();
    
    if has_body {
        block_to_tac(func.body.clone().unwrap(), &mut instructions);

        instructions.push(match func.ret_type {
            Type::I32 => TacInstruction::Return(TacVal::I32(0)),
            Type::I64 => TacInstruction::Return(TacVal::I64(0)),
            _ => panic!("Unsupported return type"),
        });
    }

    TacFuncDef::Function {
        name: func.name,
        params: func.params.into_iter().map(|(n, _)| n).collect(),
        ret_type: func.ret_type,
        body: instructions,
    }
}

fn block_to_tac(block: TypedBlock, instructions: &mut Vec<TacInstruction>) {
    match block {
        TypedBlock::Block(items) => {
            for item in items {
                match item {
                    TypedBlockItem::S(stmt) => stmt_to_tac(stmt, instructions),
                    TypedBlockItem::D(decl) => decl_to_tac(decl, instructions),
                }
            }
        }
    }
}

fn decl_to_tac(decl: TypedDecl, instructions: &mut Vec<TacInstruction>) {
    match decl {
        TypedDecl::Variable(v) => {
            let val = expr_to_tac(v.init_expr, instructions);
            instructions.push(TacInstruction::Copy {
                src: val,
                dest: TacVal::Var(v.name, v.var_type),
            });
        }
    }
}

fn stmt_to_tac(stmt: TypedStmt, instructions: &mut Vec<TacInstruction>) {
    match stmt {
        TypedStmt::Return(expr) => {
            let val = expr_to_tac(expr, instructions);
            instructions.push(TacInstruction::Return(val));
        }
        TypedStmt::Expr(expr) => {
            expr_to_tac(expr, instructions);
        }
        TypedStmt::Block(stmts) => {
            for s in stmts {
                stmt_to_tac(s, instructions);
            }
        }
        TypedStmt::While {
            condition,
            body,
            label,
        } => {
            let start_label = label.clone();
            let end_label = make_loop_label();

            instructions.push(TacInstruction::Label(start_label.clone()));
            let cond_val = expr_to_tac(condition, instructions);
            instructions.push(TacInstruction::JumpIfZero {
                condition: cond_val,
                target: end_label.clone(),
            });

            stmt_to_tac(*body, instructions);

            instructions.push(TacInstruction::Jump {
                target: start_label,
            });
            instructions.push(TacInstruction::Label(end_label));
        }
        TypedStmt::Break { label } => {
            instructions.push(TacInstruction::Jump { target: label });
        }
        TypedStmt::Continue { label } => {
            instructions.push(TacInstruction::Jump { target: label });
        }
        TypedStmt::Null => {}
    }
}

fn expr_to_tac(expr: TypedExpr, instructions: &mut Vec<TacInstruction>) -> TacVal {
    match expr.kind {
        TypedExprKind::Int32(v) => TacVal::I32(v),
        TypedExprKind::Int64(v) => TacVal::I64(v),
        TypedExprKind::Var(name) => TacVal::Var(name, expr.ty),
        TypedExprKind::Unary { op, expr: inner } => {
            let src = expr_to_tac(*inner, instructions);
            let dst = TacVal::Var(make_temporary(), expr.ty);
            instructions.push(TacInstruction::Unary {
                op: convert_unop(op),
                src,
                dest: dst.clone(),
            });
            dst
        }
        TypedExprKind::Binary { op, lhs, rhs } => {
            if matches!(op, BinaryOp::And | BinaryOp::Or) {
                return short_circuit_logic(op, *lhs, *rhs, instructions);
            }
            let src1 = expr_to_tac(*lhs, instructions);
            let src2 = expr_to_tac(*rhs, instructions);
            let dst = TacVal::Var(make_temporary(), expr.ty);
            instructions.push(TacInstruction::Binary {
                op: convert_binop(op),
                src1,
                src2,
                dest: dst.clone(),
            });
            dst
        }
        TypedExprKind::Assign { lhs, rhs } => {
            let r = expr_to_tac(*rhs, instructions);
            match lhs.kind {
                TypedExprKind::Var(name) => {
                    instructions.push(TacInstruction::Copy {
                        src: r.clone(),
                        dest: TacVal::Var(name.clone(), lhs.ty.clone()),
                    });
                    TacVal::Var(name, lhs.ty)
                }
                _ => panic!("Invalid lvalue in assignment"),
            }
        }
        TypedExprKind::IfThenElse {
            cond,
            then_expr,
            else_expr,
        } => {
            let result = TacVal::Var(make_temporary(), expr.ty);
            let else_label = make_cond_else();
            let end_label = make_cond_end();

            let c = expr_to_tac(*cond, instructions);
            instructions.push(TacInstruction::JumpIfZero {
                condition: c,
                target: else_label.clone(),
            });

            let v1 = expr_to_tac(*then_expr, instructions);
            instructions.push(TacInstruction::Copy {
                src: v1,
                dest: result.clone(),
            });
            instructions.push(TacInstruction::Jump {
                target: end_label.clone(),
            });

            instructions.push(TacInstruction::Label(else_label));
            let v2 = expr_to_tac(*else_expr, instructions);
            instructions.push(TacInstruction::Copy {
                src: v2,
                dest: result.clone(),
            });
            instructions.push(TacInstruction::Label(end_label));

            result
        }
        TypedExprKind::FunctionCall { name, args } => {
            let arg_vals = args
                .into_iter()
                .map(|a| expr_to_tac(a, instructions))
                .collect();
            let dst = TacVal::Var(make_temporary(), expr.ty);
            instructions.push(TacInstruction::FunCall {
                fun_name: name,
                args: arg_vals,
                dest: dst.clone(),
            });
            dst
        }
        TypedExprKind::Cast {
            expr: inner,
            target,
        } => {
            let src = expr_to_tac(*inner, instructions);
            let dst = TacVal::Var(make_temporary(), target.clone());
            match (&src, &target) {
                (TacVal::I64(_) | TacVal::Var(_, Type::I64), Type::I32) => {
                    instructions.push(TacInstruction::Truncate {
                        src,
                        dest: dst.clone(),
                    });
                }
                (TacVal::I32(_) | TacVal::Var(_, Type::I32), Type::I64) => {
                    instructions.push(TacInstruction::SignExtend {
                        src,
                        dest: dst.clone(),
                    });
                }
                (TacVal::Var(_, t1), t2) if t1 == t2 => {
                    instructions.push(TacInstruction::Copy {
                        src,
                        dest: dst.clone(),
                    });
                }
                _ => panic!("Unsupported cast"),
            }
            dst
        }
    }
}

fn short_circuit_logic(
    op: BinaryOp,
    expr1: TypedExpr,
    expr2: TypedExpr,
    instructions: &mut Vec<TacInstruction>,
) -> TacVal {
    let result_name = make_temporary();
    let result = TacVal::Var(result_name.clone(), Type::I32);
    match op {
        BinaryOp::And => {
            let false_label = make_and_false();
            let end_label = make_and_end();

            let v1 = expr_to_tac(expr1, instructions);
            instructions.push(TacInstruction::JumpIfZero {
                condition: v1.clone(),
                target: false_label.clone(),
            });
            let v2 = expr_to_tac(expr2, instructions);
            instructions.push(TacInstruction::JumpIfZero {
                condition: v2.clone(),
                target: false_label.clone(),
            });

            instructions.push(TacInstruction::Copy {
                src: TacVal::I32(1),
                dest: result.clone(),
            });
            instructions.push(TacInstruction::Jump {
                target: end_label.clone(),
            });
            instructions.push(TacInstruction::Label(false_label));
            instructions.push(TacInstruction::Copy {
                src: TacVal::I32(0),
                dest: result.clone(),
            });
            instructions.push(TacInstruction::Label(end_label));
        }
        BinaryOp::Or => {
            let true_label = make_or_true();
            let end_label = make_or_end();

            let v1 = expr_to_tac(expr1, instructions);
            instructions.push(TacInstruction::JumpIfNotZero {
                condition: v1,
                target: true_label.clone(),
            });
            let v2 = expr_to_tac(expr2, instructions);
            instructions.push(TacInstruction::JumpIfNotZero {
                condition: v2,
                target: true_label.clone(),
            });

            instructions.push(TacInstruction::Copy {
                src: TacVal::I32(0),
                dest: result.clone(),
            });
            instructions.push(TacInstruction::Jump {
                target: end_label.clone(),
            });
            instructions.push(TacInstruction::Label(true_label));
            instructions.push(TacInstruction::Copy {
                src: TacVal::I32(1),
                dest: result.clone(),
            });
            instructions.push(TacInstruction::Label(end_label));
        }
        _ => unreachable!(),
    }
    result
}

fn convert_unop(op: UnaryOp) -> TacUnaryOp {
    match op {
        UnaryOp::Negate => TacUnaryOp::Negate,
        UnaryOp::Complement => TacUnaryOp::Complement,
        UnaryOp::Not => TacUnaryOp::Not,
    }
}

fn convert_binop(op: BinaryOp) -> TacBinaryOp {
    match op {
        BinaryOp::Add => TacBinaryOp::Add,
        BinaryOp::Subtract => TacBinaryOp::Subtract,
        BinaryOp::Multiply => TacBinaryOp::Multiply,
        BinaryOp::Divide => TacBinaryOp::Divide,
        BinaryOp::Remainder => TacBinaryOp::Remainder,
        BinaryOp::Equal => TacBinaryOp::Equal,
        BinaryOp::NotEqual => TacBinaryOp::NotEqual,
        BinaryOp::LessThan => TacBinaryOp::LessThan,
        BinaryOp::LessOrEqual => TacBinaryOp::LessOrEqual,
        BinaryOp::GreaterThan => TacBinaryOp::GreaterThan,
        BinaryOp::GreaterOrEqual => TacBinaryOp::GreaterOrEqual,
        BinaryOp::And | BinaryOp::Or => unreachable!(),
    }
}
