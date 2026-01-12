use crate::{
    parser::{
        Block, BlockItem, Decl, Expr, FuncDef, Program, Stmt, make_loop_label, make_temporary,
    },
    pipe,
};
use std::collections::HashMap;

struct MapEntry {
    unique_name: String,
    from_current_block: bool,
}

pub fn semantic_analysis(program: Program) -> Program {
    pipe!(program => variable_resolution_pass => loop_labeling_pass)
}

pub fn variable_resolution_pass(program: Program) -> Program {
    match program {
        Program::Program { main_func } => {
            let new_main = resolve_func_def(main_func);
            Program::Program {
                main_func: new_main,
            }
        }
    }
}

pub fn loop_labeling_pass(program: Program) -> Program {
    match program {
        Program::Program { main_func } => Program::Program {
            main_func: label_func_def(main_func),
        },
    }
}

fn label_func_def(func: FuncDef) -> FuncDef {
    match func {
        FuncDef::Function { name, body } => {
            let body = label_block(body, None);
            FuncDef::Function { name, body }
        }
    }
}

fn label_block(block: Block, current_label: Option<String>) -> Block {
    let Block::Block(items) = block;
    let items = items
        .into_iter()
        .map(|item| label_block_item(item, current_label.clone()))
        .collect();
    Block::Block(items)
}

fn label_block_item(item: BlockItem, current_label: Option<String>) -> BlockItem {
    match item {
        BlockItem::D(d) => BlockItem::D(d),
        BlockItem::S(s) => BlockItem::S(label_statement(s, current_label)),
    }
}

pub fn label_statement(stmt: Stmt, current_label: Option<String>) -> Stmt {
    match stmt {
        Stmt::Break { .. } => {
            let label = current_label.expect("Semantic Error: 'break' statement outside of loop");
            Stmt::Break { label }
        }

        Stmt::Continue { .. } => {
            let label =
                current_label.expect("Semantic Error: 'continue' statement outside of loop");
            Stmt::Continue { label }
        }

        Stmt::While {
            condition, body, ..
        } => {
            let new_label = make_loop_label();
            let labeled_body = Box::new(label_statement(*body, Some(new_label.clone())));
            Stmt::While {
                condition,
                body: labeled_body,
                label: new_label,
            }
        }

        Stmt::DoWhile {
            body, condition, ..
        } => {
            let new_label = make_loop_label();
            let labeled_body = Box::new(label_statement(*body, Some(new_label.clone())));
            Stmt::DoWhile {
                body: labeled_body,
                condition,
                label: new_label,
            }
        }

        Stmt::For {
            init,
            condition,
            post,
            body,
            ..
        } => {
            let new_label = make_loop_label();
            let labeled_body = Box::new(label_statement(*body, Some(new_label.clone())));
            Stmt::For {
                init,
                condition,
                post,
                body: labeled_body,
                label: new_label,
            }
        }

        Stmt::If {
            condition,
            then_case,
            else_case,
        } => Stmt::If {
            condition,
            then_case: Box::new(label_statement(*then_case, current_label.clone())),
            else_case: else_case.map(|e| Box::new(label_statement(*e, current_label.clone()))),
        },

        Stmt::Compound(block) => Stmt::Compound(label_block(block, current_label)),

        Stmt::Return(_) | Stmt::Expression(_) | Stmt::Null => stmt,
    }
}

fn resolve_func_def(func: FuncDef) -> FuncDef {
    match func {
        FuncDef::Function { name, body } => {
            let mut variable_map = HashMap::new();
            let body = resolve_block(body, &mut variable_map);
            FuncDef::Function { name, body }
        }
    }
}

fn resolve_block(block: Block, variable_map: &mut HashMap<String, MapEntry>) -> Block {
    let Block::Block(items) = block;

    let new_items = items
        .into_iter()
        .map(|item| resolve_block_item(item, variable_map))
        .collect();

    Block::Block(new_items)
}

fn resolve_block_item(item: BlockItem, variable_map: &mut HashMap<String, MapEntry>) -> BlockItem {
    match item {
        BlockItem::D(decl) => BlockItem::D(resolve_decl(decl, variable_map)),
        BlockItem::S(stmt) => BlockItem::S(resolve_stmt(stmt, variable_map)),
    }
}

fn resolve_decl(decl: Decl, variable_map: &mut HashMap<String, MapEntry>) -> Decl {
    match decl {
        Decl::Declaration { name, expr } => {
            if variable_map.contains_key(&name)
                && variable_map
                    .get(&name)
                    .expect("Already checked!")
                    .from_current_block
            {
                panic!("Duplicate variable declaration: {}", name);
            }

            let unique_name = make_temporary();
            variable_map.insert(
                name,
                MapEntry {
                    unique_name: unique_name.clone(),
                    from_current_block: true,
                },
            );

            let new_expr = expr.map(|e| resolve_expr(e, variable_map));

            Decl::Declaration {
                name: unique_name,
                expr: new_expr,
            }
        }
    }
}

fn resolve_stmt(stmt: Stmt, variable_map: &mut HashMap<String, MapEntry>) -> Stmt {
    match stmt {
        Stmt::Return(expr) => Stmt::Return(resolve_expr(expr, variable_map)),
        Stmt::Expression(expr) => Stmt::Expression(resolve_expr(expr, variable_map)),
        Stmt::Null => Stmt::Null,

        Stmt::If {
            condition,
            then_case,
            else_case,
        } => Stmt::If {
            condition: resolve_expr(condition, variable_map),
            then_case: Box::new(resolve_stmt(*then_case, variable_map)),
            else_case: else_case.map(|e| Box::new(resolve_stmt(*e, variable_map))),
        },

        Stmt::Compound(block) => {
            let mut new_map = copy_variable_map(variable_map);
            Stmt::Compound(resolve_block(block, &mut new_map))
        }

        Stmt::Break { label } => Stmt::Break { label },
        Stmt::Continue { label } => Stmt::Continue { label },

        Stmt::While {
            condition,
            body,
            label,
        } => {
            let body = Box::new(resolve_stmt(*body, variable_map));
            Stmt::While {
                condition: resolve_expr(condition, variable_map),
                body,
                label,
            }
        }

        Stmt::DoWhile {
            body,
            condition,
            label,
        } => {
            let body = Box::new(resolve_stmt(*body, variable_map));
            Stmt::DoWhile {
                body,
                condition: resolve_expr(condition, variable_map),
                label,
            }
        }

        Stmt::For {
            init,
            condition,
            post,
            body,
            label,
        } => {
            let mut new_map = copy_variable_map(variable_map);

            let init = match init {
                crate::parser::ForInit::InitDecl(d) => {
                    crate::parser::ForInit::InitDecl(resolve_decl(d, &mut new_map))
                }
                crate::parser::ForInit::InitExpr(e) => {
                    crate::parser::ForInit::InitExpr(e.map(|ex| resolve_expr(ex, &mut new_map)))
                }
            };

            let condition = condition.map(|e| resolve_expr(e, &mut new_map));
            let post = post.map(|e| resolve_expr(e, &mut new_map));

            let body = Box::new(resolve_stmt(*body, &mut new_map));

            Stmt::For {
                init,
                condition,
                post,
                body,
                label,
            }
        }
    }
}

fn resolve_expr(expr: Expr, variable_map: &mut HashMap<String, MapEntry>) -> Expr {
    match expr {
        Expr::Constant(c) => Expr::Constant(c),
        Expr::Var(v) => {
            if let Some(map_entry) = variable_map.get(&v) {
                Expr::Var(map_entry.unique_name.clone())
            } else {
                panic!("Undeclared variable: {}", v);
            }
        }
        Expr::Unary(op, inner) => {
            let resolved_inner = resolve_expr(*inner, variable_map);
            Expr::Unary(op, Box::new(resolved_inner))
        }
        Expr::Binary(op, left, right) => {
            let left_resolved = resolve_expr(*left, variable_map);
            let right_resolved = resolve_expr(*right, variable_map);
            Expr::Binary(op, Box::new(left_resolved), Box::new(right_resolved))
        }
        Expr::Assignment(left, right) => match *left {
            Expr::Var(_) => {
                let left_resolved = resolve_expr(*left, variable_map);
                let right_resolved = resolve_expr(*right, variable_map);
                Expr::Assignment(Box::new(left_resolved), Box::new(right_resolved))
            }
            _ => panic!("Invalid lvalue in assignment!"),
        },
        Expr::Conditional(expr, expr1, expr2) => {
            let expr_r = resolve_expr(*expr, variable_map);
            let expr1_r = resolve_expr(*expr1, variable_map);
            let expr2_r = resolve_expr(*expr2, variable_map);
            Expr::Conditional(Box::new(expr_r), Box::new(expr1_r), Box::new(expr2_r))
        }
    }
}

fn copy_variable_map(variable_map: &HashMap<String, MapEntry>) -> HashMap<String, MapEntry> {
    variable_map
        .iter()
        .map(|(k, v)| {
            (
                k.clone(),
                MapEntry {
                    unique_name: v.unique_name.clone(),
                    from_current_block: false,
                },
            )
        })
        .collect()
}
