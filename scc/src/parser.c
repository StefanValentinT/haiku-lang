#ifndef PARSER_H
#define PARSER_H

#include "syntax.c"
#include <string.h>

Program parse(char* source);

#endif
#if __INCLUDE_LEVEL__ == 0

#include "dynarray.c"
#include "hashmap.c"
#include "lexer.c"
#include "log.c"
#include "stdlib.h"
#include "syntax.c"
#include <stdio.h>

#define expect(x) expectElse(x, "Expected " #x ".")

// internal functions
Token expectElse(TokenKind k, char* msg);
Term parseTerm(void);
DeclarationData parseDeclaration(void);
Statement parseStatement(void);
Type parseType(void);

bool hadError;
bool inPanicMode;

// String -> Type
Map typeDefinitions;

Token expectElse(TokenKind k, char* msg)
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

Term parseTermFactor(void)
{
	Token recBinderOpt = (Token){TOK_IDENTIFIER, NULL, 0, -1};
	DynArray arr;
	Token tok = nextToken();
	SourceInfo s = (SourceInfo){tok.line};

	switch (tok.type)
	{
	case TOK_IDENTIFIER:
		if (peekToken().type == TOK_LEFT_PAREN)
		{
			nextToken();
			arr = initArray(2, sizeof(Term));
			while (peekToken().type != TOK_RIGHT_PAREN)
			{
				appendArray(&arr, newTerm(parseTerm()));
				if (peekToken().type != TOK_RIGHT_PAREN)
				{
					expect(TOK_COMMA);
				}
			}
			expect(TOK_RIGHT_PAREN);
			return (Term){APPLICATION, {.app = {tok.start, tok.len, (Term*)arr.items, (int)arr.count}}, s};
		}
		else
		{
			return (Term){VAR, {.var = {tok.start, tok.len}}, s};
		}
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
		Term t = parseTerm();
		expectElse(TOK_RIGHT_PAREN, "Parentheted expression requires a closing parenthese.");
		return t;
	}
	case TOK_LEFT_BRACE:
		if (peekToken().type == TOK_RIGHT_BRACE)
		{
			nextToken();
			return (Term){BLOCK, {.block = {.stmts = NULL, ._stmtCount = 0}}, s};
		}
		arr = initArray(16, sizeof(Statement));
		Term* trailingExp = NULL;
		while (peekToken().type != TOK_RIGHT_BRACE)
		{
			Token peek = peekToken();
			if (peek.type == TOK_VAL || peek.type == TOK_VAR)
			{
				Statement newS = (Statement){DECLARATION, {.declaration = parseDeclaration()}, s};
				appendArray(&arr, (void*)&newS);
			}
			else
			{
				Term expr = parseTerm();
				if (peekToken().type == TOK_SEMICOLON)
				{
					nextToken();
					Statement newS = (Statement){UNIT_EXPRESSION, {.unit_expression = expr}, s};
					appendArray(&arr, (void*)&newS);
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
		expectElse(TOK_RIGHT_BRACE, "Block requires a closing brace.");
		return (Term
		){BLOCK, {.block = {.stmts = (Statement*)arr.items, ._stmtCount = (int)arr.count, .exp = trailingExp}}, s};
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
	case TOK_FUN:
		arr = initArray(2, sizeof(Formal));
		if (peekToken().type == TOK_IDENTIFIER)
		{
			recBinderOpt = nextToken();
		}
		if (peekToken().type == TOK_LEFT_PAREN)
		{
			nextToken();
			while (peekToken().type != TOK_RIGHT_PAREN)
			{
				Token name = nextToken();
				Type* t = NULL;
				if (peekToken().type == TOK_COLON)
				{
					nextToken();
					t = newType(parseType());
				}
				Formal formal = (Formal){.name = name.start, ._len = name.len, .type = t};
				appendArray(&arr, (void*)&formal);
				Token peek = peekToken();
				if (peek.type == TOK_COMMA)
				{
					nextToken();
				}
				else if (peek.type == TOK_RIGHT_PAREN)
				{
					break;
				}
				else
				{
					logFatal("Bad token: %.*s", peek.len, peek.start);
				}
			}
			expect(TOK_RIGHT_PAREN);
		}
		else
		{
			logFatal("%i: Expected formals list or recursive bind but got %d", tok.line, tok.type);
		}
		expect(TOK_ARROW);
		return (Term){FUNCTION,
		              {.fun =
		                   {
		                       recBinderOpt.start,
		                       recBinderOpt.len,
		                       (Formal*)arr.items,
		                       (int)arr.count,
		                       newTerm(parseTerm()),
		                   }},
		              s};
	}

	logFatal("Unparseable term, this could indicate a compiler bug.");
	// unreachable
}

BinaryOpKind tokToBinOp(TokenKind t)
{
	switch (t)
	{
	case TOK_STAR:
		return MULTIPLY;
	case TOK_MINUS:
		return SUBTRACT;
	case TOK_PLUS:
		return ADD;
	case TOK_SLASH:
		return DIVIDE;
	case TOK_PERCENT:
		return REMAINDER;
	case TOK_OR:
		return OR;
	case TOK_AND:
		return AND;
	}
}

Term parseTerm(void)
{
	Term term = parseTermFactor();
	while (true)
	{
		Token next = peekToken();
		SourceInfo s = term.info;
		// parses left-to-rigth associatively
		// TODO: add precedence
		switch (next.type)
		{
		// Binary
		case TOK_PLUS:
		case TOK_MINUS:
		case TOK_STAR:
		case TOK_SLASH:
		case TOK_PERCENT:
		case TOK_AND:
		case TOK_OR:
			nextToken();
			BinaryOpKind binOp = tokToBinOp(next.type);
			term = (Term){BINARY_OP, {.binOp = {binOp, newTerm(term), newTerm(parseTermFactor())}}, s};
			break;

		case TOK_COLON:
			nextToken();
			term = (Term){TYPED, {.typed = {newTerm(term), parseType()}}};
			break;

		// Postfix
		case TOK_DOT_STAR:
			nextToken();
			term = (Term){DEREF, .data = {.deref = {newTerm(term)}}, s};
			break;

		// no postfix or binary expression left
		default:
			return term;
		}
	}
}

DeclarationData parseDeclaration(void)
{
	bool mutable = nextToken().type == TOK_VAL ? false : true;
	Token ident = expectElse(TOK_IDENTIFIER, "Declaration keyword must be followed by identfier.");
	Type* typePtr = NULL;
	if (peekToken().type == TOK_COLON)
	{
		nextToken();
		typePtr = newType(parseType());
	}
	Term* exp = NULL;
	if (peekToken().type == TOK_EQUAL)
	{
		nextToken();
		exp = newTerm(parseTerm());
	}
	expectElse(TOK_SEMICOLON, "Unterminated declaration.");
	DeclarationData d = (DeclarationData){
	    .mutable = mutable,
	    .name = ident.start,
	    .type = typePtr,
	    ._len = ident.len,
	    .exp = exp,
	};
	return d;
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
			expect(TOK_SEMICOLON);
			mapPut(&typeDefinitions, ident.start, ident.len, (void*)type);
			break;

		default:
			logFatal("Expected start of declaration at line %d, but got %d", next.line, next.type);
			break;
		}
		next = peekToken();
	}
	return (Program){declarations, count};
}

#endif
