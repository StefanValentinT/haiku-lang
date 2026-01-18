use std::collections::HashMap;

use crate::ast::ast_type::Type;
use crate::ast::typed_ast::*;
use crate::ast::untyped_ast::*;

#[derive(Clone)]
struct SymbolEntry {
    ty: Type,
}

type SymbolTable = HashMap<String, SymbolEntry>;

pub fn typecheck(program: Program) -> TypedProgram {
    let mut symbols = SymbolTable::new();
    let Program::Program(funcs) = program;

    for f in &funcs {
        declare_function(f, &mut symbols);
    }

    let mut typed_funs = Vec::new();
    for f in funcs {
        typed_funs.push(typecheck_fun_decl(f, &symbols));
    }

    TypedProgram {
        functions: typed_funs,
    }
}

fn declare_function(decl: &FunDecl, symbols: &mut SymbolTable) {
    let param_types = decl.params.iter().map(|(_, t)| t.clone()).collect();
    let fun_ty = Type::FunType {
        params: param_types,
        ret: Box::new(decl.ret_type.clone()),
    };

    if let Some(old) = symbols.get(&decl.name) {
        if old.ty != fun_ty {
            panic!("Conflicting declarations of function {}", decl.name);
        }
    }

    symbols.insert(decl.name.clone(), SymbolEntry { ty: fun_ty });
}

fn typecheck_fun_decl(decl: FunDecl, globals: &SymbolTable) -> TypedFunDecl {
    let SymbolEntry { ty, .. } = globals.get(&decl.name).unwrap().clone();

    let (param_types, ret_ty) = match ty {
        Type::FunType { params, ret } => (params, *ret),
        _ => unreachable!(),
    };

    let mut locals = globals.clone();

    let typed_params: Vec<(String, Type)> = decl
        .params
        .into_iter()
        .zip(param_types.into_iter())
        .map(|((name, _), ty)| {
            locals.insert(name.clone(), SymbolEntry { ty: ty.clone() });
            (name, ty)
        })
        .collect();

    let body = decl
        .body
        .map(|b| TypedBlock::Block(typecheck_block(&b, &mut locals, &ret_ty)));

    TypedFunDecl {
        name: decl.name,
        params: typed_params,
        ret_type: ret_ty,
        body,
    }
}

fn typecheck_block(
    block: &Block,
    symbols: &mut SymbolTable,
    expected_ret: &Type,
) -> Vec<TypedBlockItem> {
    let Block::Block(items) = block;

    items
        .iter()
        .map(|item| match item {
            BlockItem::D(d) => TypedBlockItem::D(typecheck_decl(d, symbols)),
            BlockItem::S(s) => TypedBlockItem::S(typecheck_stmt(s, symbols, expected_ret)),
        })
        .collect()
}

fn typecheck_decl(decl: &Decl, symbols: &mut SymbolTable) -> TypedDecl {
    match decl {
        Decl::Variable(v) => {
            let init = typecheck_expr(&v.init_expr, symbols);
            if init.ty != v.var_type {
                panic!(
                    "Type mismatch in variable '{}': expected {:?}, got {:?}",
                    v.name, v.var_type, init.ty
                );
            }

            symbols.insert(
                v.name.clone(),
                SymbolEntry {
                    ty: v.var_type.clone(),
                },
            );

            TypedDecl::Variable(TypedVarDecl {
                name: v.name.clone(),
                init_expr: init,
                var_type: v.var_type.clone(),
            })
        }
    }
}

fn typecheck_stmt(stmt: &Stmt, symbols: &mut SymbolTable, expected_ret: &Type) -> TypedStmt {
    match stmt {
        Stmt::Return(expr) => {
            let typed = typecheck_expr(expr, symbols);
            if &typed.ty != expected_ret {
                panic!(
                    "Return type mismatch: expected {:?}, got {:?}",
                    expected_ret, typed.ty
                );
            }
            TypedStmt::Return(typed)
        }

        Stmt::Expression(expr) => TypedStmt::Expr(typecheck_expr(expr, symbols)),

        Stmt::Null => TypedStmt::Null,

        Stmt::Compound(block) => {
            let mut inner = symbols.clone();
            let stmts = typecheck_block(block, &mut inner, expected_ret)
                .into_iter()
                .filter_map(|i| match i {
                    TypedBlockItem::S(s) => Some(s),
                    _ => None,
                })
                .collect();
            TypedStmt::Block(stmts)
        }

        Stmt::While {
            condition,
            body,
            label,
        } => {
            let cond = typecheck_expr(condition, symbols);
            if cond.ty != Type::I32 {
                panic!("While condition must be I32");
            }
            let body = Box::new(typecheck_stmt(body, symbols, expected_ret));
            TypedStmt::While {
                condition: cond,
                body,
                label: label.clone(),
            }
        }

        Stmt::Break { label } => TypedStmt::Break {
            label: label.clone(),
        },

        Stmt::Continue { label } => TypedStmt::Continue {
            label: label.clone(),
        },
    }
}

fn typecheck_expr(expr: &Expr, symbols: &mut SymbolTable) -> TypedExpr {
    match &expr.kind {
        ExprKind::Int32(v) => TypedExpr {
            ty: Type::I32,
            kind: TypedExprKind::Int32(*v),
        },

        ExprKind::Int64(v) => TypedExpr {
            ty: Type::I64,
            kind: TypedExprKind::Int64(*v),
        },

        ExprKind::Var(name) => {
            let entry = symbols
                .get(name)
                .unwrap_or_else(|| panic!("Undefined variable {}", name));
            TypedExpr {
                ty: entry.ty.clone(),
                kind: TypedExprKind::Var(name.clone()),
            }
        }

        ExprKind::Unary(op, e) => {
            let inner = typecheck_expr(e, symbols);
            TypedExpr {
                ty: inner.ty.clone(),
                kind: TypedExprKind::Unary {
                    op: op.clone(),
                    expr: Box::new(inner),
                },
            }
        }

        ExprKind::Binary(op, lhs, rhs) => {
            let l = typecheck_expr(lhs, symbols);
            let r = typecheck_expr(rhs, symbols);

            if l.ty != r.ty {
                panic!("Binary op type mismatch: {:?} vs {:?}", l.ty, r.ty);
            }

            TypedExpr {
                ty: l.ty.clone(),
                kind: TypedExprKind::Binary {
                    op: op.clone(),
                    lhs: Box::new(l),
                    rhs: Box::new(r),
                },
            }
        }

        ExprKind::Assign(lhs, rhs) => {
            let l = typecheck_expr(lhs, symbols);
            let r = typecheck_expr(rhs, symbols);

            if l.ty != r.ty {
                panic!("Assignment type mismatch: {:?} vs {:?}", l.ty, r.ty);
            }

            TypedExpr {
                ty: l.ty.clone(),
                kind: TypedExprKind::Assign {
                    lhs: Box::new(l),
                    rhs: Box::new(r),
                },
            }
        }

        ExprKind::IfThenElse(cond, t, e) => {
            let c = typecheck_expr(cond, symbols);
            let t = typecheck_expr(t, symbols);
            let e = typecheck_expr(e, symbols);

            if t.ty != e.ty {
                panic!("If branches must have same type");
            }

            TypedExpr {
                ty: t.ty.clone(),
                kind: TypedExprKind::IfThenElse {
                    cond: Box::new(c),
                    then_expr: Box::new(t),
                    else_expr: Box::new(e),
                },
            }
        }

        ExprKind::FunctionCall(name, args) => {
            let entry = symbols
                .get(name)
                .unwrap_or_else(|| panic!("Undefined function {}", name));

            let (params, ret) = match &entry.ty {
                Type::FunType { params, ret } => (params.clone(), *ret.clone()),
                _ => panic!("{} is not a function", name),
            };

            if params.len() != args.len() {
                panic!("Wrong number of arguments to {}", name);
            }

            let typed_args: Vec<_> = args.iter().map(|a| typecheck_expr(a, symbols)).collect();

            for (arg, param_ty) in typed_args.iter().zip(params.iter()) {
                if &arg.ty != param_ty {
                    panic!(
                        "Argument type mismatch in call to {}: expected {:?}, got {:?}",
                        name, param_ty, arg.ty
                    );
                }
            }

            TypedExpr {
                ty: ret,
                kind: TypedExprKind::FunctionCall {
                    name: name.clone(),
                    args: typed_args,
                },
            }
        }

        ExprKind::Cast { expr, target } => {
            let inner = typecheck_expr(expr, symbols);
            TypedExpr {
                ty: target.clone(),
                kind: TypedExprKind::Cast {
                    expr: Box::new(inner),
                    target: target.clone(),
                },
            }
        }
    }
}
