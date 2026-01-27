use crate::ast::ast_type::{BinaryOp, Const, ExecTime, Type, UnaryOp};

#[derive(Debug, Clone)]
pub struct TypedProgram {
    pub functions: Vec<TypedFunDecl>,
}

#[derive(Debug, Clone)]
pub struct TypedFunDecl {
    pub name: String,
    pub params: Vec<(String, Type)>,
    pub ret_type: Type,
    pub body: Option<TypedBlock>,
    pub exec_time: ExecTime,
}

#[derive(Debug, Clone)]
pub enum TypedDecl {
    Variable(TypedVarDecl),
}

#[derive(Debug, Clone)]
pub struct TypedVarDecl {
    pub name: String,
    pub init_expr: TypedExpr,
    pub var_type: Type,
}

#[derive(Debug, Clone)]
pub enum TypedBlock {
    Block(Vec<TypedBlockItem>),
}

#[derive(Debug, Clone)]
pub enum TypedBlockItem {
    S(TypedStmt),
    D(TypedDecl),
}

#[derive(Debug, Clone)]
pub enum TypedStmt {
    Return(TypedExpr),
    Expr(TypedExpr),
    Block(Vec<TypedStmt>),

    While {
        condition: TypedExpr,
        body: Box<TypedStmt>,
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

#[derive(Debug, Clone)]
pub struct TypedExpr {
    pub ty: Type,
    pub kind: TypedExprKind,
}

#[derive(Debug, Clone)]
pub enum TypedExprKind {
    Constant(Const),

    Var(String),

    Unary {
        op: UnaryOp,
        expr: Box<TypedExpr>,
    },

    Binary {
        op: BinaryOp,
        lhs: Box<TypedExpr>,
        rhs: Box<TypedExpr>,
    },

    Assign {
        lhs: Box<TypedExpr>,
        rhs: Box<TypedExpr>,
    },

    IfThenElse {
        cond: Box<TypedExpr>,
        then_expr: Box<TypedExpr>,
        else_expr: Box<TypedExpr>,
    },

    FunctionCall {
        name: String,
        args: Vec<TypedExpr>,
    },

    Dereference(Box<TypedExpr>),
    AddrOf(Box<TypedExpr>),

    ArrayLiteral(Vec<TypedExpr>),
    ArrayIndex(Box<TypedExpr>, Box<TypedExpr>),

    SliceFromArray(Box<TypedExpr>),
    SliceLen(Box<TypedExpr>),

    Cast {
        expr: Box<TypedExpr>,
        target: Type,
    },
}
