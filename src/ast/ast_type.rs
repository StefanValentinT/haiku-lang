#[derive(Debug, PartialEq, Eq, Clone, Hash)]
pub enum Type {
    I32,
    I64,
    F64,

    Unit,

    FunType { params: Vec<Type>, ret: Box<Type> },
    Pointer { referenced: Box<Type> },
    Array { element: Box<Type>, size: i32 },
}

#[derive(Debug, Clone, PartialEq)]
pub enum Const {
    I32(i32),
    I64(i64),
    F64(f64),
}

#[derive(Debug, Clone, PartialEq)]
pub enum UnaryOp {
    Complement,
    Negate,
    Not,
}

#[derive(Debug, Clone, PartialEq)]
pub enum BinaryOp {
    Add,
    Subtract,
    Multiply,
    Divide,
    Remainder,

    And,
    Or,
    Equal,
    NotEqual,
    LessThan,
    LessOrEqual,
    GreaterThan,
    GreaterOrEqual,
}
