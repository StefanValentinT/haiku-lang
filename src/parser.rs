use crate::{
    lexer::Token,
    queue::{IsQueue, Queue},
};

#[derive(Debug)]
pub enum Program {
    Program { main_func: FuncDef },
}

#[derive(Debug)]
pub enum FuncDef {
    Function { name: String, body: Stmt },
}

#[derive(Debug)]
pub enum Stmt {
    Return(Expr),
}

#[derive(Debug)]
pub enum Expr {
    Constant(i32),
    Unary(UnaryOp, Box<Expr>),
}

#[derive(Debug)]
pub enum UnaryOp {
    Complement,
    Negate,
}

pub fn parse(tokens: Queue<Token>) -> Program {
    let mut tokens = tokens;
    let main_func = parse_func_def(&mut tokens);
    Program::Program { main_func }
}

fn parse_func_def(tokens: &mut Queue<Token>) -> FuncDef {
    expect(Token::Keyword("int".to_string()), tokens);
    let name = match tokens.remove().unwrap() {
        Token::Identifier(name) => name,
        other => panic!("Syntax Error: Expected function name, got {:?}", other),
    };
    expect(Token::OpenParen, tokens);

    let _type = match tokens.remove().unwrap() {
        Token::Keyword(name) => name,
        other => panic!(
            "Syntax Error: Expected void (nothing else supported), got {:?}",
            other
        ),
    };

    expect(Token::CloseParen, tokens);
    expect(Token::OpenBrace, tokens);
    let body = parse_statement(tokens);
    expect(Token::CloseBrace, tokens);

    //Just one main func program now over
    expect(Token::EOF, tokens);

    FuncDef::Function { name, body }
}

fn parse_statement(tokens: &mut Queue<Token>) -> Stmt {
    expect(Token::Keyword("return".to_string()), tokens);
    let expr = parse_expr(tokens);
    expect(Token::Semicolon, tokens);
    Stmt::Return(expr)
}

fn parse_expr(tokens: &mut Queue<Token>) -> Expr {
    let tok = tokens.remove().unwrap();
    match tok {
        Token::IntLiteral(val) => Expr::Constant(val),
        Token::Tilde | Token::Neg => {
            let op = parse_unop(tok);
            let expr = parse_expr(tokens);
            Expr::Unary(op, Box::new(expr))
        }
        Token::OpenParen => {
            let inner = parse_expr(tokens);
            expect(Token::CloseParen, tokens);
            inner
        }
        _ => panic!("Syntax Error: Malformed expression, got {:?}", tok),
    }
}

fn parse_unop(tok: Token) -> UnaryOp {
    match tok {
        Token::Neg => UnaryOp::Negate,
        Token::Tilde => UnaryOp::Complement,
        Token::Decrement => todo!(),
        _ => panic!("Syntax Error: Expected unary operator, got {:?}", tok),
    }
}

fn expect(expected: Token, tokens: &mut Queue<Token>) -> Token {
    let actual = tokens.remove().unwrap();
    if actual != expected {
        panic!("Syntax Error: Expected {:?} but got {:?}", expected, actual)
    } else {
        return actual;
    }
}
