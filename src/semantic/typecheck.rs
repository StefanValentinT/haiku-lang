use std::collections::HashMap;

use crate::ast::ast_type::Type;
use crate::ast::typed_ast::*;
use crate::ast::untyped_ast::*;

#[derive(Clone)]
struct SymbolEntry {
    ty: Type,
    defined: bool,
}

type SymbolTable = HashMap<String, SymbolEntry>;

pub fn typecheck(program: Program) -> TypedProgram {
    let mut symbols = SymbolTable::new();
    let mut typed_funs = Vec::new();

    let Program::Program(funcs) = program;

    for f in &funcs {
        declare_function(f, &mut symbols);
    }

    for f in funcs {
        typed_funs.push(typecheck_fun_decl(f, &mut symbols));
    }

    TypedProgram {
        functions: typed_funs,
    }
}

fn declare_function(decl: &FunDecl, symbols: &mut SymbolTable) {
    let param_types = decl
        .params
        .iter()
        .map(|(_, ty)| ty.clone())
        .collect::<Vec<_>>();
    let fun_ty = Type::FunType {
        params: param_types,
        ret: Box::new(decl.ret_type.clone()),
    };

    if let Some(old) = symbols.get(&decl.name) {
        if old.ty != fun_ty {
            panic!("Conflicting declarations of function {}", decl.name);
        }
    }

    symbols.insert(
        decl.name.clone(),
        SymbolEntry {
            ty: fun_ty,
            defined: decl.body.is_some(),
        },
    );
}

fn typecheck_fun_decl(decl: FunDecl, symbols: &mut SymbolTable) -> TypedFunDecl {
    let SymbolEntry { ty, .. } = symbols.get(&decl.name).unwrap().clone();

    let (param_types, ret_ty) = match ty {
        Type::FunType { params, ret } => (params, *ret),
        _ => unreachable!(),
    };

    let mut local_symbols = symbols.clone();

    let typed_params: Vec<(String, Type)> = decl
        .params
        .into_iter()
        .zip(param_types.into_iter())
        .map(|((name, _), ty)| {
            local_symbols.insert(
                name.clone(),
                SymbolEntry {
                    ty: ty.clone(),
                    defined: true,
                },
            );
            (name, ty)
        })
        .collect();

    let body_items = decl
        .body
        .map(|b| typecheck_block(&b, &mut local_symbols))
        .unwrap_or_else(|| Vec::new());

    let body_block = TypedBlock::Block(body_items);

    TypedFunDecl {
        name: decl.name,
        params: typed_params,
        ret_type: ret_ty,
        body: body_block,
    }
}

fn typecheck_block(block: &Block, symbols: &mut SymbolTable) -> Vec<TypedBlockItem> {
    let Block::Block(items) = block;

    items
        .iter()
        .map(|item| match item {
            BlockItem::D(decl) => {
                let typed_decl = typecheck_decl(decl, symbols);
                TypedBlockItem::D(typed_decl)
            }
            BlockItem::S(stmt) => {
                let typed_stmt = typecheck_stmt(stmt, symbols);
                TypedBlockItem::S(typed_stmt)
            }
        })
        .collect()
}

fn typecheck_decl(decl: &Decl, symbols: &mut SymbolTable) -> TypedDecl {
    match decl {
        Decl::Variable(v) => {
            let typed_init = typecheck_expr(&v.init_expr, symbols);
            if typed_init.ty != v.var_type {
                panic!(
                    "Type mismatch in variable '{}': expected {:?}, got {:?}",
                    v.name, v.var_type, typed_init.ty
                );
            }
            symbols.insert(
                v.name.clone(),
                SymbolEntry {
                    ty: v.var_type.clone(),
                    defined: true,
                },
            );
            TypedDecl::Variable(TypedVarDecl {
                name: v.name.clone(),
                init_expr: typecheck_expr(&v.init_expr, symbols),
                var_type: v.var_type.clone(),
            })
        }
    }
}

fn typecheck_stmt(stmt: &Stmt, symbols: &mut SymbolTable) -> TypedStmt {
    match stmt {
        Stmt::Return(expr) => TypedStmt::Return(typecheck_expr(expr, symbols)),
        Stmt::Expression(expr) => TypedStmt::Expr(typecheck_expr(expr, symbols)),
        Stmt::Null => TypedStmt::Null,

        Stmt::Compound(block) => {
            let body_items = typecheck_block(block, symbols);
            let mut stmts = vec![];

            for item in body_items {
                match item {
                    TypedBlockItem::S(s) => stmts.push(s),
                    TypedBlockItem::D(d) => match d {
                        TypedDecl::Variable(v) => {
                            stmts.push(TypedStmt::Expr(TypedExpr {
                                ty: v.var_type.clone(),
                                kind: v.init_expr.kind.clone(),
                            }));
                        }
                    },
                }
            }

            TypedStmt::Block(stmts)
        }

        Stmt::While {
            condition,
            body,
            label,
        } => TypedStmt::While {
            condition: typecheck_expr(condition, symbols),
            body: Box::new(typecheck_stmt(body, symbols)),
            label: label.clone(),
        },

        Stmt::Break { label } => TypedStmt::Break {
            label: label.to_string(),
        },
        Stmt::Continue { label } => TypedStmt::Continue {
            label: label.to_string(),
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
                panic!(
                    "Type mismatch in binary expression: {:?} vs {:?}",
                    l.ty, r.ty
                );
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
                panic!("Type mismatch in assignment: {:?} vs {:?}", l.ty, r.ty);
            }

            TypedExpr {
                ty: l.ty.clone(),
                kind: TypedExprKind::Assign {
                    lhs: Box::new(l),
                    rhs: Box::new(r),
                },
            }
        }

        ExprKind::IfThenElse(cond, then_e, else_e) => {
            let c = typecheck_expr(cond, symbols);
            let t = typecheck_expr(then_e, symbols);
            let e = typecheck_expr(else_e, symbols);

            if t.ty != e.ty {
                panic!("Type mismatch in if expression: {:?} vs {:?}", t.ty, e.ty);
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

            let typed_args = args.iter().map(|a| typecheck_expr(a, symbols)).collect();

            TypedExpr {
                ty: ret,
                kind: TypedExprKind::FunctionCall {
                    name: name.clone(),
                    args: typed_args,
                },
            }
        }

        ExprKind::Cast { expr: e, target } => {
            let inner = typecheck_expr(e, symbols);
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
