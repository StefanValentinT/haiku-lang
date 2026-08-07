#ifndef PARSER_H
#define PARSER_H

#include "syntax.c"
#include <string.h>

Program parse(char* source);

#endif
#if __INCLUDE_LEVEL__ == 0

#include "hashmap.c"
#include "lexer.c"
#include "log.c"
#include "stdlib.h"
#include "syntax.c"

// internal functions
Token expect(TokenKind k, char* msg);
Term parseTerm(void);
DeclarationData parseDeclaration(void);
Statement parseStatement(void);
Type parseType(void);

bool hadError;
bool inPanicMode;

// String -> Type
Map typeDefinitions;

Token expect(TokenKind k, char* msg)
{
	Token t = nextToken();
	if (t.type == k)
	{
		return t;
	}
	else
	{
		logError(msg);
		hadError = true;
		return makeErrorToken(msg);
	}
}

int32_t parseNumber(const char* start, int len)
{
	if (start == NULL || len <= 0)
	{
		logFatal("No number literals constructed by the lexer are empty.");
	}
	int32_t result = 0;
	for (int i = 0; i < len; i++)
	{
		result = result + 10 * (start[i] - '0');
	}
	return result;
}

Term parseTermPrimary(void)
{
	Token tok = nextToken();
	SourceInfo s = (SourceInfo){tok.line};

	switch (tok.type)
	{
	case TOK_IDENTIFIER:
		return (Term){VAR, {.var = {tok.start, tok.len}}, s};
	case TOK_BUILTIN:
		return (Term){BUILTIN_VAR, {.builtinVar = {tok.start, tok.len}}, s};
	case TOK_NUMBER:
		// TODO: Typed number literals
		// For now all number literals are implictly i32
		return (Term){CONSTANT, {.constant = {{.i32Val = parseNumber(tok.start, tok.len)}, (Type){I32, {0}}}}, s};
	case TOK_STRING:
		return (Term){STRING, {.string = {tok.start, tok.len}}, s};
	case TOK_AMPERSAND:
		return (Term){REF, {.ref = {newTerm(parseTerm())}}, s};

	case TOK_LEFT_PAREN:
	{
	}
		Term t = parseTerm();
		expect(TOK_RIGHT_PAREN, "Parentheted expression requires a closing parenthese.");
		return t;
		break;

	case TOK_LEFT_BRACE:
	{
	}
		Token next = peekToken();
		if (next.type == TOK_RIGHT_BRACE)
		{
			nextToken();
			return (Term){BLOCK, {.block = {.stmts = NULL, ._stmtCount = 0}}, s};
		}
		int capacity = 16;
		int count = 0;
		Statement* stmts = malloc((size_t)capacity * sizeof(Statement));
		Term* trailingExp = NULL;
		while (next.type != TOK_RIGHT_BRACE)
		{
			next = peekToken();
			if (next.type == TOK_VAL || next.type == TOK_VAR)
			{
				Statement newS = (Statement){DECLARATION, {.declaration = parseDeclaration()}, s};

				if (count >= capacity)
				{
					capacity *= 2;
					Statement* temp = realloc(stmts, (size_t)capacity * sizeof(Statement));
					if (temp == NULL)
					{
						logFatal("Could not allocate enough memory to parse all statements.");
					}
					stmts = temp;
				}
				stmts[count++] = newS;
			}
			else
			{
				Term expr = parseTerm();

				if (peekToken().type == TOK_SEMICOLON)
				{
					nextToken();
					Statement newS = (Statement){UNIT_EXPRESSION, {.unit_expression = expr}, s};

					if (count >= capacity)
					{
						capacity *= 2;
						Statement* temp = realloc(stmts, (size_t)capacity * sizeof(Statement));
						if (temp == NULL)
						{
							logFatal("Could not allocate enough memory to parse all statements.");
						}
						stmts = temp;
					}
					stmts[count++] = newS;
				}
				else if (peekToken().type == TOK_RIGHT_BRACE)
				{
					trailingExp = newTerm(expr);
					break;
				}
				else
				{
					logFatal("Expression in block must be followed by a semicolon or closing brace.");
				}
			}
		}
		expect(TOK_RIGHT_BRACE, "Block requires a closing brace.");
		return (Term){BLOCK, {.block = {.stmts = stmts, ._stmtCount = count, .exp = trailingExp}}, s};
	case TOK_RIGHT_PAREN:
		logError("Stray right paren in source code.");
		hadError = true;
		break;
	case TOK_RIGHT_BRACE:
		logError("Stray right brace in source code.");
		hadError = true;
		break;
	case TOK_RETURN:
		return (Term){RETURN, {.retur = {newTerm(parseTerm())}}, s};
	case TOK_BREAK:
		return (Term){BREAK, {0}, s};
	case TOK_CONTINUE:
		return (Term){CONTINUE, {0}, s};
	}

	logFatal("Unparseable term, this could indicate a compiler bug.");
	// unreachable
}

Term parseTerm(void)
{
	Term term = parseTermPrimary();
	while (true)
	{
		Token next = peekToken();
		SourceInfo s = term.info;
		if (next.type == TOK_DOT_STAR)
		{
			nextToken();
			term = (Term){DEREF, .data = {.deref = {newTerm(term)}}, s};
		}
		else
		{
			break;
		}
	}
}

DeclarationData parseDeclaration(void)
{
	bool mutable = nextToken().type == TOK_VAL ? false : true;
	Token ident = expect(TOK_IDENTIFIER, "Declaration keyword must be followed by identfier.");
	expect(TOK_EQUAL, "Declaration requires an equal sign.");
	Term* exp = newTerm(parseTerm());
	expect(TOK_SEMICOLON, "Unterminated declaration.");
	return (DeclarationData){
	    .mutable = mutable,
	    .name = ident.start,
	    ._len = ident.len,
	    .exp = exp,
	};
}

Type parseType(void)
{
	Token tok = nextToken();
	switch (tok.type)
	{
	case TOK_I8:
		return (Type){I8, {0}};
	case TOK_I16:
		return (Type){I16, {0}};
	case TOK_I32:
		return (Type){I32, {0}};
	case TOK_I64:
		return (Type){I64, {0}};
	case TOK_U8:
		return (Type){U8, {0}};
	case TOK_U16:
		return (Type){U16, {0}};
	case TOK_U32:
		return (Type){U32, {0}};
	case TOK_U64:
		return (Type){U64, {0}};
	case TOK_F32:
		return (Type){F32, {0}};
	case TOK_F64:
		return (Type){F64, {0}};
	default:
		logFatal("Unrecognized type: %s", tok.start);
	}
}

Program parse(char* source)
{
	mapInit(&typeDefinitions);

	initLexer(source);

	Token next = peekToken();
	int capacity = 8;
	int count = 0;
	DeclarationData* declarations = malloc((size_t)capacity * sizeof(DeclarationData));

	while (next.type != TOK_EOF)
	{
		DeclarationData newDecl = {0};
		switch (next.type)
		{
		case TOK_VAL:
		case TOK_VAR:
			newDecl = parseDeclaration();
			if (count >= capacity)
			{
				capacity = capacity * 2;
				DeclarationData* temp = realloc(declarations, (size_t)capacity * sizeof(DeclarationData));
				if (temp == NULL)
				{
					logFatal("Could not allocate enough memory to parse all "
					         "declarations.");
				}
				declarations = temp;
			}
			declarations[count] = newDecl;
			count++;
			break;
		case TOK_TYPE:
		{
		}
			nextToken();
			Token ident = nextToken();
			if (nextToken().type != TOK_EQUAL)
			{
				logFatal("Type definitions misses equal sign after identifier.");
			}
			Type* type = newType(parseType());
			mapPut(&typeDefinitions, ident.start, ident.len, (void*)type);
			break;

		default:
			logError("Epxected start of declaration at %d.", next.line);
		}
		next = peekToken();
	}
}

#endif
