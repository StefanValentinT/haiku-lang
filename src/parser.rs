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

#[derive(Debug, Clone)]
pub enum Expr {
    Constant(i32),
    Unary(UnaryOp, Box<Expr>),
    Binary(BinaryOp, Box<Expr>, Box<Expr>),
}

#[derive(Debug, Clone)]
pub enum UnaryOp {
    Complement,
    Negate,
}

#[derive(Debug, Clone)]
pub enum BinaryOp {
    Add,
    Subtract,
    Multiply,
    Divide,
    Remainder,
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
    let expr = parse_expr(tokens, 0);
    expect(Token::Semicolon, tokens);
    Stmt::Return(expr)
}

fn parse_factor(tokens: &mut Queue<Token>) -> Expr {
    let next_token = tokens.remove().unwrap();
    match next_token {
        Token::IntLiteral(val) => Expr::Constant(val),
        Token::Tilde | Token::Minus => {
            let op = parse_unop(next_token);
            let inner_expr = parse_factor(tokens);
            Expr::Unary(op, Box::new(inner_expr))
        }
        Token::OpenParen => {
            let inner_exp = parse_expr(tokens, 0);
            expect(Token::CloseParen, tokens);
            inner_exp
        }
        _ => panic!("Malformed factor!"),
    }
}

fn parse_expr(tokens: &mut Queue<Token>, min_prec: i32) -> Expr {
    let mut left = parse_factor(tokens);

    loop {
        let next_token = match tokens.peek() {
            Ok(tok) => tok.clone(),
            Err(_) => break,
        };

        if !is_token_binop(&next_token) {
            break;
        }

        let prec = precedence(&next_token);
        if prec < min_prec {
            break;
        }

        let op = parse_binop(tokens.remove().unwrap());
        let right = parse_expr(tokens, prec + 1);
        left = Expr::Binary(op, Box::new(left), Box::new(right));
    }

    left
}

fn is_token_binop(tok: &Token) -> bool {
    matches!(
        tok,
        Token::Plus | Token::Minus | Token::Multiply | Token::Divide | Token::Remainder
    )
}

fn precedence(tok: &Token) -> i32 {
    use Token::*;
    match tok {
        Minus => 45,
        Plus => 45,
        Multiply => 50,
        Divide => 50,
        Remainder => 50,
        _ => panic!("{:#?} has no precedence.", tok),
    }
}

fn parse_unop(tok: Token) -> UnaryOp {
    match tok {
        Token::Minus => UnaryOp::Negate,
        Token::Tilde => UnaryOp::Complement,
        Token::Decrement => todo!(),
        _ => panic!("Syntax Error: Expected unary operator, got {:?}", tok),
    }
}

fn parse_binop(tok: Token) -> BinaryOp {
    use BinaryOp::*;
    match tok {
        Token::Plus => Add,
        Token::Minus => Subtract,
        Token::Multiply => Multiply,
        Token::Remainder => Remainder,
        Token::Divide => Divide,
        _ => panic!("Syntax Error: Expected binary operator, got {:?}", tok),
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
