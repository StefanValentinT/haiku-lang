use crate::queue::*;

#[derive(Debug, Clone, PartialEq)]
pub enum Token {
    Identifier(String),
    IntLiteral(i32),
    Keyword(String),

    OpenParen,
    CloseParen,
    OpenBrace,
    CloseBrace,
    Semicolon,

    //unary operators
    Tilde,
    Neg,
    Decrement,

    EOF,
}
use crate::queue::*;

const KEYWORDS: [&str; 32] = [
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "restrict", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned",
    "void", "while",
];

fn is_boundary(c: char) -> bool {
    matches!(
        c,
        ' ' | '\t'
            | '\n'
            | '('
            | ')'
            | '{'
            | '}'
            | ';'
            | ','
            | '+'
            | '-'
            | '*'
            | '/'
            | '%'
            | '='
            | '<'
            | '>'
    )
}

pub fn lex_string(input: String) -> Queue<Token> {
    let mut input = str_to_queue(input);
    let mut tokens: Queue<Token> = Queue::new();

    while !input.is_empty() {
        consume_while(&mut input, |c| matches!(c, ' ' | '\t' | '\n'));

        if input.is_empty() {
            break;
        }

        let c = match input.peek() {
            Ok(c) => c,
            Err(_) => break,
        };

        match c {
            '/' => {
                input.consume();
                if !skip_if_comment(&mut input) {
                    //implemnte division
                }
            }

            'a'..='z' | 'A'..='Z' | '_' => {
                tokens.add(lex_identifier(&mut input));
            }

            '0'..='9' => {
                tokens.add(lex_int(&mut input));
            }

            '(' => {
                st(Token::OpenParen, &mut input, &mut tokens);
            }
            ')' => {
                st(Token::CloseParen, &mut input, &mut tokens);
            }
            '{' => {
                st(Token::OpenBrace, &mut input, &mut tokens);
            }
            '}' => {
                st(Token::CloseBrace, &mut input, &mut tokens);
            }
            ';' => {
                st(Token::Semicolon, &mut input, &mut tokens);
            }
            '~' => {
                st(Token::Tilde, &mut input, &mut tokens);
            }
            '-' => {
                if input.is_there(1, '-') {
                    input.consume();
                    input.consume();
                    tokens.add(Token::Decrement);
                } else {
                    input.consume();
                    tokens.add(Token::Neg);
                }
            }

            _ => {
                panic!("Lexer error: unexpected character '{}'", c);
            }
        }
    }

    tokens.add(Token::EOF);

    tokens
}

fn st(t: Token, input: &mut Queue<char>, tokens: &mut Queue<Token>) {
    input.consume();
    tokens.add(t);
}

fn consume_while<F>(input: &mut Queue<char>, mut pred: F)
where
    F: FnMut(char) -> bool,
{
    while let Ok(c) = input.peek() {
        if pred(c) {
            input.consume();
        } else {
            break;
        }
    }
}

fn next_needs_to_be_boundary(input: &Queue<char>) {
    if let Ok(c) = input.peek() {
        if !is_boundary(c) {
            panic!(
                "Invalid token: next character '{}' must be a token boundary",
                c
            );
        }
    }
}

fn is_keyword(s: &str) -> bool {
    KEYWORDS.contains(&s)
}

fn lex_identifier(input: &mut Queue<char>) -> Token {
    let mut ident = String::new();

    while let Ok(c) = input.peek() {
        if c.is_alphanumeric() || c == '_' {
            ident.push(input.remove().unwrap());
        } else {
            break;
        }
    }

    next_needs_to_be_boundary(input);

    if is_keyword(&ident) {
        Token::Keyword(ident)
    } else {
        Token::Identifier(ident)
    }
}

fn lex_int(input: &mut Queue<char>) -> Token {
    let mut value = 0i32;

    while let Ok(c) = input.peek() {
        if c.is_ascii_digit() {
            value = value * 10 + (input.remove().unwrap() as i32 - '0' as i32);
        } else {
            break;
        }
    }

    next_needs_to_be_boundary(input);

    Token::IntLiteral(value)
}

fn skip_if_comment(input: &mut Queue<char>) -> bool {
    match input.peek() {
        Ok('/') => {
            input.consume();
            consume_while(input, |c| c != '\n');
            true
        }
        Ok('*') => {
            input.consume();
            let mut prev = '\0';
            while let Ok(c) = input.remove() {
                if prev == '*' && c == '/' {
                    break;
                }
                prev = c;
            }
            true
        }
        _ => false,
    }
}
