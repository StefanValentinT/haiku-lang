use crate::ast::ast_type::{BinaryOp, Const, Type, UnaryOp};

#[derive(Debug)]
pub enum Program {
    Program(Vec<FunDecl>),
}

#[derive(Debug, Clone)]
pub enum Decl {
    Variable(VarDecl),
}

#[derive(Debug, Clone)]
pub struct VarDecl {
    pub name: String,
    pub init_expr: Expr,
    pub var_type: Type,
}

#[derive(Debug, Clone)]
pub struct FunDecl {
    pub name: String,
    pub params: Vec<(String, Type)>,
    pub body: Option<Block>,
    pub ret_type: Type,
}

#[derive(Debug, Clone)]
pub enum Block {
    Block(Vec<BlockItem>),
}

#[derive(Debug, Clone)]
pub enum BlockItem {
    S(Stmt),
    D(Decl),
}

#[derive(Debug, Clone)]
pub enum Stmt {
    Return(Expr),
    Expression(Expr),
    Compound(Block),

    While {
        condition: Expr,
        body: Box<Stmt>,
        label: String,
    },

    Break {
        label: String,
    },
    Continue {
        label: String,
    },

    Null,
}

#[derive(Debug, Clone, PartialEq)]
pub struct Expr {
    pub ty: Option<Type>,
    pub kind: ExprKind,
}

#[derive(Debug, Clone, PartialEq)]
pub enum ExprKind {
    Constant(Const),
    Var(String),

    Unary(UnaryOp, Box<Expr>),
    Binary(BinaryOp, Box<Expr>, Box<Expr>),

    Assign(Box<Expr>, Box<Expr>),

    IfThenElse(Box<Expr>, Box<Expr>, Box<Expr>),

    FunctionCall(String, Vec<Expr>),

    Cast { expr: Box<Expr>, target: Type },
}
