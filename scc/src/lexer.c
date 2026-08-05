#ifndef LEXER_H
#define LEXER_H

typedef enum
{
	TOK_LEFT_PAREN,
	TOK_RIGHT_PAREN,
	TOK_LEFT_BRACE,
	TOK_RIGHT_BRACE,
	TOK_COMMA,
	TOK_SEMICOLON,
	TOK_DOT,
	TOK_COLON,
	TOK_EQUAL,
	TOK_ARROW,

	TOK_IDENTIFIER,
	TOK_BUILTIN,
	TOK_STRING,
	TOK_NUMBER,

	TOK_FUN,
	TOK_IF,
	TOK_ELSE,
	TOK_FOR,
	TOK_RETURN,
	TOK_BREAK,
	TOK_CONTINUE,
	TOK_VAL,
	TOK_VAR,

	TOK_ERROR,
	TOK_EOF,
} TokenKind;

typedef struct
{
	TokenKind type;
	const char* start;
	int len;
	int line;
} Token;

typedef struct
{
	const char* start;
	const char* current;
	int line;
} Lexer;

void initLexer(const char* source);
Token lexToken(void);

#endif
#if __INCLUDE_LEVEL__ == 0

#include "log.c"
#include "string.h"
#include <stdbool.h>
#include <stdlib.h>

Lexer lexer;

void initLexer(const char* source)
{
	lexer.start = source;
	lexer.current = source;
	lexer.line = 0;
}

bool isAtEnd(void) { return *lexer.current == '\0'; }

Token makeToken(TokenKind t)
{
	Token token;
	token.type = t;
	token.start = lexer.start;
	token.len = (int)(lexer.current - lexer.start);
	token.line = lexer.line;
	return token;
}

Token makeErrorToken(const char* message)
{
	Token token;
	token.type = TOK_ERROR;
	token.start = message;
	token.len = (int)strlen(message);
	token.line = lexer.line;
	return token;
}

char advance(void)
{
	lexer.current++;
	return lexer.current[-1];
}

char peek(void) { return *lexer.current; }

bool isNext(char expected)
{
	char c = advance();
	if (c == expected)
		return true;
	return false;
}

void skipWhitespace(void)
{
	while (true)
	{
		char n = peek();
		switch (n)
		{
		case '\n':
			lexer.line++;
		case ' ':
		case '\t':
		case '\r':
			advance();
			break;
		case '#':
			advance();
			if (isNext('#'))
			{
				int delimLength = 2;
				int tryEndLength = 0;
				while (isNext('#'))
					delimLength++;
				while (tryEndLength != delimLength)
				{
					while (!isNext('#') && !isAtEnd())
						;
					if (isAtEnd())
						logFatal("Unterminated block comment.");
					tryEndLength = 1;
					while (isNext('#'))
						tryEndLength++;
				}
			}
			else
			{
				while (peek() != '\n' && !isAtEnd())
					advance();
			}
			break;
		default:
			return;
		}
	}
}

Token lexString(void)
{
	while (peek() != '"' && !isAtEnd())
	{
		if (peek() != '\n')
			lexer.line++;
		advance();
	}
	if (isAtEnd())
		return makeErrorToken("String is not terminated.");
	advance();
	return makeToken(TOK_STRING);
}

bool isDigit(char c) { return c >= '0' && c <= '9'; }

bool isAlpha(char c)
{
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_');
}

Token lexNumber(void)
{
	while (isDigit(peek()))
		advance();
	if (peek() == '.')
	{
		advance();
		if (isDigit(peek()))
		{
			while (isDigit(peek()))
				advance();
		}
		else
		{
			return makeErrorToken(
			    "An integer literal has no members to possibly access."
			);
		}
	}
	return makeToken(TOK_NUMBER);
}

TokenKind checkKeyword(const char* key, long keyLen, TokenKind k)
{
	if ((keyLen == lexer.current - lexer.start) &&
	    (memcmp(lexer.start, key, (unsigned)keyLen) == 0))
	{
		return k;
	}
	else
	{
		return TOK_IDENTIFIER;
	}
}

TokenKind classifyIdent(void)
{
	switch (lexer.start[0])
	{
	case 'b':
		return checkKeyword("break", 5, TOK_BREAK);
	case 'c':
		return checkKeyword("continue", 8, TOK_CONTINUE);
	case 'e':
		return checkKeyword("else", 4, TOK_ELSE);
	case 'f':
		switch (lexer.start[1])
		{
		case 'u':
			return checkKeyword("fun", 3, TOK_FUN);
		case 'o':
			return checkKeyword("for", 3, TOK_FOR);
		}
	case 'i':
		return checkKeyword("if", 2, TOK_IF);
	case 'r':
		return checkKeyword("return", 6, TOK_RETURN);
	case 'v':
		switch (lexer.start[2])
		{
		case 'l':
			return checkKeyword("val", 3, TOK_VAL);
		case 'r':
			return checkKeyword("var", 3, TOK_VAR);
		}
	}

	return TOK_IDENTIFIER;
}

Token lexIdentifier(void)
{
	char p = peek();
	bool d = isDigit(p);
	bool containsDigit = false;
	while (isAlpha(p) || d)
	{
		if (d)
		{
			containsDigit = true;
		}
		advance();
		p = peek();
		d = isDigit(p);
	}
	// No keywords contain any digits
	if (!containsDigit)
	{
		return makeToken(classifyIdent());
	}
	return makeToken(TOK_IDENTIFIER);
}

Token lexBuiltin(void)
{
	char p = peek();
	while (isAlpha(p) || isDigit(p))
	{
		advance();
		p = peek();
	}
	return makeToken(TOK_BUILTIN);
}

Token lexToken(void)
{
	skipWhitespace();
	lexer.start = lexer.current;

	if (isAtEnd())
	{
		return makeToken(TOK_EOF);
	}
	char next = advance();
	if (isAlpha(next))
		return lexIdentifier();
	if (isDigit(next))
		return lexNumber();

	switch (next)
	{
	case '@':
		return lexBuiltin();
	case '(':
		return makeToken(TOK_LEFT_PAREN);
	case ')':
		return makeToken(TOK_RIGHT_PAREN);
	case '{':
		return makeToken(TOK_LEFT_BRACE);
	case '}':
		return makeToken(TOK_RIGHT_BRACE);
	case ',':
		return makeToken(TOK_COMMA);
	case ';':
		return makeToken(TOK_SEMICOLON);
	case '.':
		return makeToken(TOK_DOT);
	case ':':
		return makeToken(TOK_COLON);
	case '=':
		return makeToken(TOK_EQUAL);
	case '-':
		if (isNext('>'))
		{
			return makeToken(TOK_ARROW);
		}
		else
		{
			return makeErrorToken(
			    "Expected '>' after '-' to complete an arrow symbol."
			);
		}
	case '"':
		return lexString();
	}

	return makeErrorToken("Input can not be tokenized.");
}

#endif
