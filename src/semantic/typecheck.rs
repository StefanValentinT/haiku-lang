use std::collections::HashMap;

use crate::parser::*;

#[derive(Debug, PartialEq, Clone)]
pub enum Type {
    Int,
    FunType { param_count: i32 },
}

struct SymbolEntry {
    symbol_type: Type,
    defined: bool,
}

type SymbolTable = HashMap<String, SymbolEntry>;

pub fn typecheck(program: Program) -> Program {
    let mut symbols: SymbolTable = HashMap::new();

    if let Program::Program(funcs) = &program {
        for decl in funcs {
            typecheck_fun_decl(decl.clone(), &mut symbols);
        }
    }

    program
}

fn typecheck_decl(decl: &Decl, symbols: &mut SymbolTable) {
    match decl {
        Decl::Variable(v) => typecheck_var_decl(v, symbols),
        Decl::Function(f) => typecheck_fun_decl(f.clone(), symbols),
    }
}

fn typecheck_var_decl(decl: &VarDecl, symbols: &mut SymbolTable) {
    symbols.insert(
        decl.name.clone(),
        SymbolEntry {
            symbol_type: Type::Int,
            defined: false,
        },
    );
    if let Some(init_expr) = &decl.init_expr {
        typecheck_expr(init_expr, symbols);
    }
}

fn typecheck_fun_decl(decl: FunDecl, symbols: &mut SymbolTable) {
    let fun_type = Type::FunType {
        param_count: decl.params.len() as i32,
    };
    let has_body = decl.body.is_some();
    let mut already_defined = false;

    if symbols.contains_key(&decl.name) {
        let old_decl = (symbols.get(&decl.name).expect("Checked it!")).clone();
        if old_decl.symbol_type != fun_type {
            panic!("Incompatible function declarations.")
        }
        already_defined = old_decl.defined;
        if already_defined && has_body {
            panic!("Function is defined more than once.")
        }
    }

    let defined = already_defined || has_body;
    symbols.insert(
        decl.name,
        SymbolEntry {
            symbol_type: fun_type,
            defined,
        },
    );

    if has_body {
        for param in decl.params {
            symbols.insert(
                param,
                SymbolEntry {
                    symbol_type: Type::Int,
                    defined: false,
                },
            );
        }
        typecheck_block(&decl.body.expect("Checked it!"), symbols);
    }
}

fn typecheck_block(block: &Block, symbols: &mut SymbolTable) {
    if let Block::Block(items) = block {
        for item in items {
            match item {
                BlockItem::D(decl) => typecheck_decl(decl, symbols),
                BlockItem::S(stmt) => typecheck_stmt(stmt, symbols),
            }
        }
    }
}

fn typecheck_stmt(stmt: &Stmt, symbols: &mut SymbolTable) {
    match stmt {
        Stmt::Return(expr) => typecheck_expr(expr, symbols),
        Stmt::Expression(expr) => typecheck_expr(expr, symbols),
        Stmt::If {
            condition,
            then_case,
            else_case,
        } => {
            typecheck_expr(condition, symbols);
            typecheck_stmt(then_case, symbols);
            if let Some(else_case) = else_case {
                typecheck_stmt(else_case, symbols);
            }
        }
        Stmt::Compound(block) => typecheck_block(block, symbols),
        Stmt::While {
            condition, body, ..
        } => {
            typecheck_expr(condition, symbols);
            typecheck_stmt(body, symbols);
        }
        Stmt::DoWhile {
            body, condition, ..
        } => {
            typecheck_stmt(body, symbols);
            typecheck_expr(condition, symbols);
        }
        Stmt::For {
            init,
            condition,
            post,
            body,
            ..
        } => {
            match init {
                ForInit::InitDecl(decl) => typecheck_var_decl(decl, symbols),
                ForInit::InitExpr(expr_opt) => {
                    if let Some(expr) = expr_opt {
                        typecheck_expr(expr, symbols);
                    }
                }
            }
            if let Some(cond) = condition {
                typecheck_expr(cond, symbols);
            }
            if let Some(post_expr) = post {
                typecheck_expr(post_expr, symbols);
            }
            typecheck_stmt(body, symbols);
        }
        Stmt::Break { .. } | Stmt::Continue { .. } | Stmt::Null => { /* nothing */ }
    }
}

fn typecheck_expr(e: &Expr, symbols: &mut SymbolTable) {
    match e {
        Expr::Constant(_) => { /* Constants are always int */ }
        Expr::Var(v) => match symbols.get(v) {
            Some(entry) => {
                if entry.symbol_type != Type::Int {
                    panic!("Function name used as variable: {}", v);
                }
            }
            None => panic!("Undefined variable: {}", v),
        },
        Expr::Unary(_op, expr) => {
            typecheck_expr(expr, symbols);
        }
        Expr::Binary(_op, lhs, rhs) => {
            typecheck_expr(lhs, symbols);
            typecheck_expr(rhs, symbols);
        }
        Expr::Assignment(lhs, rhs) => {
            typecheck_expr(lhs, symbols);
            typecheck_expr(rhs, symbols);
        }
        Expr::Conditional(cond, then_expr, else_expr) => {
            typecheck_expr(cond, symbols);
            typecheck_expr(then_expr, symbols);
            typecheck_expr(else_expr, symbols);
        }
        Expr::FunctionCall(f, args) => {
            let entry = symbols
                .get(f)
                .unwrap_or_else(|| panic!("Undefined function: {}", f));
            match entry.symbol_type {
                Type::Int => panic!("Variable used as function name: {}", f),
                Type::FunType { param_count } => {
                    if param_count != args.len() as i32 {
                        panic!(
                            "Function `{}` called with wrong number of arguments. Expected {}, got {}",
                            f,
                            param_count,
                            args.len()
                        );
                    }
                    for arg in args {
                        typecheck_expr(arg, symbols);
                    }
                }
            }
        }
    }
}
