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
#define UNREACHABLE                                                                                                    \
	{                                                                                                                  \
		printf("UNREACHABLE reached in file %s:%d.\n", __FILE__, __LINE__);                                            \
		abort();                                                                                                       \
	}

// internal functions
Token expectElse(TokenKind k, char* msg);
Term parseTerm(void);
DeclarationData parseDeclaration(void);
Statement parseStatement(void);
Type parseType(void);

typedef struct
{
	int shadowDepth;
	bool mutable;
} ScopeData;

typedef struct Scope
{
	struct Scope* parent;
	// String -> ScopeData
	Map* vars;
} Scope;

Scope* scope = NULL;
bool hadError;
bool inPanicMode;

// String -> Type
Map typeDefinitions;

Token expectElse(TokenKind k, char* msg)
{
	Token t = nextToken();
	if (t.kind == k)
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
		result = result * 10 + (start[i] - '0');
	}
	return result;
}

void enterScope(void)
{
	Scope* newScope = malloc(sizeof(Scope));

	if (newScope == NULL)
	{
		logFatal("Could not allocate enough memory for new scope.");
	}

	newScope->vars = malloc(sizeof(Map));
	if (newScope->vars == NULL)
	{
		free(newScope);
		logFatal("Could not allocate enough memory for scope map.");
	}

	mapInit(newScope->vars);
	newScope->parent = scope;
	scope = newScope;
}

void leaveScope(void)
{
	if (scope == NULL)
	{
		logFatal("Can't leave global scope exists.");
	}

	Scope* oldScope = scope;
	scope = scope->parent;

	mapFree(oldScope->vars);
	free(oldScope->vars);
	free(oldScope);
}

ScopeData* lookup(const char* varName, int len)
{
	for (Scope* current = scope; current != NULL; current = current->parent)
	{
		ScopeData* val = mapGet(current->vars, varName, len);

		if (val != NULL)
			return val;
	}

	return NULL;
}

void declare(const char* varName, int len, bool mutable)
{
	if (mapHas(scope->vars, varName, len))
	{
		logFatal("Invalid redeclaration of %.*s in same scope.", len, varName);
	}

	ScopeData* previous = lookup(varName, len);

	int shadowDepth = 0;

	if (previous != NULL)
	{
		shadowDepth = previous->shadowDepth + 1;
	}

	ScopeData* newData = malloc(sizeof(ScopeData));

	if (newData == NULL)
	{
		logFatal("Could not allocate ScopeData.");
	}

	*newData = (ScopeData){.shadowDepth = shadowDepth, .mutable = mutable};

	mapPut(scope->vars, varName, len, newData);
}

void printScopeData(void* val)
{
	ScopeData* scopeData = (ScopeData*)val;
	printf("{depth: %d, mutable: %s}", scopeData->shadowDepth, scopeData->mutable ? "true" : "false");
}
void printScope(void)
{
	printf("--- Scope ---\n");
	for (Scope* current = scope; current != NULL; current = current->parent)
	{
		mapPrint(current->vars, printScopeData);
	}
	printf("-------------\n");
}

Term parseAtom(void)
{
	Token tok = nextToken();
	ScopeData* scopeData;
	SourceInfo s = (SourceInfo){tok.line};
	switch (tok.kind)
	{
	case TOK_IDENTIFIER:
		scopeData = lookup(tok.start, tok.len);
		if (!scopeData)
		{
			logFatal("Undefined variable %.*s in line %d.", tok.len, tok.start, tok.line);
		}
		return (Term){VAR, {.var = {tok.start, tok.len}}, s};
	case TOK_NUMBER:
		// TODO: Typed number literals
		// For now all number literals are implictly i32
		return (Term){CONSTANT, {.constant = {{.i32Val = parseNumber(tok.start, tok.len)}, (Type){I32, {0}}}}, s};
	case TOK_STRING:
		return (Term){STRING, {.string = {tok.start, tok.len}}, s};
	default:
		logFatal("Not an atom: %d.", tok.kind);
		abort();
	}
}

bool startsAtom(TokenKind tok)
{
	switch (tok)
	{
	case TOK_IDENTIFIER:
	case TOK_NUMBER:
	case TOK_STRING:
		return true;
	default:
		return false;
	}
}

bool startsFactor(TokenKind tok)
{
	switch (tok)
	{
	case TOK_LEFT_PAREN:
	case TOK_STRUCT:
	case TOK_UNION:
		return true;
	default:
		if (startsAtom(tok))
		{
			return true;
		}
		return false;
	}
}

DynArray parseInitList(void)
{
	DynArray initList;
	initArray(4, sizeof(Member));

	while (true)
	{
		Token name = expect(TOK_IDENTIFIER);

		expect(TOK_EQUAL);

		Term* value = newTerm(parseTerm());
		Member* memberPtr = malloc(sizeof(Member));
		*memberPtr = (Member){name.start, name.len, value};

		appendArray(&initList, memberPtr);

		if (peekToken().kind == TOK_COMMA)
		{
			nextToken();
		}
		else
		{
			break;
		}
	}

	return initList;
}

DynArray parseArgList(void)
{
	DynArray initList;
	initArray(4, sizeof(Term));
	while (true)
	{
		Term* valuePtr = newTerm(parseTerm());
		appendArray(&initList, valuePtr);

		if (peekToken().kind == TOK_COMMA)
		{
			nextToken();
		}
		else
		{
			break;
		}
	}
	return initList;
}

Term parseFactor(void)
{
	DynArray initList;
	bool isUnion;
	Term t;

	Token tok = peekToken();
	SourceInfo s = (SourceInfo){tok.line};
	switch (tok.kind)
	{
	case TOK_LEFT_PAREN:
		nextToken();
		t = parseTerm();
		expect(TOK_RIGHT_PAREN);
		return t;
		break;
	case TOK_UNION:
	case TOK_STRUCT:
		isUnion = tok.kind == TOK_STRUCT ? false : true;
		nextToken();
		expect(TOK_LEFT_BRACE);
		if (peekToken().kind != TOK_RIGHT_BRACE)
		{
			initList = parseInitList();
			expect(TOK_RIGHT_BRACE);
			return (Term){STRUCTURE, {.structure = {isUnion, (Member*)initList.items, (int)initList.count}}, s};
		}
		else
		{
			nextToken();
			return (Term){STRUCTURE, {.structure = {isUnion, NULL, 0}}, s};
		}
		break;
	default:
		if (startsAtom(tok.kind))
		{
			return parseAtom();
		}
		logFatal("Not a factor: %d.", tok.kind);
		abort();
		break;
	}
}

bool startsPostfix(TokenKind tok)
{
	if (startsFactor(tok))
	{
		return true;
	}
	return false;
}

Term parsePostfix(void)

{
	Term post;
	Token peek = peekToken();
	SourceInfo s = (SourceInfo){peek.line};

	if (peek.kind == TOK_LEFT_BRACE)
	{
		Token ident = expect(TOK_IDENTIFIER);
		expect(TOK_LEFT_BRACE);
		Type* type = (Type*)mapGet(&typeDefinitions, ident.start, ident.len);
		if (type == NULL)
		{
			logFatal("Type not defined, but used in line %d.", ident.line);
		}
		if (type->kind != STRUCT_TYPE)
		{
			logFatal("Type to be initialized not a structure, in line %d.", ident.line);
		}
		DynArray inits = parseInitList();
		expect(TOK_LEFT_BRACE);
		post =
		    (Term){STRUCTURE, {.structure = {type->data.structure.isUnion, (Member*)inits.items, (int)inits.count}}, s};
	}
	else
	{
		post = parseFactor();
	}

	DynArray list;
	while (true)
	{
		peek = peekToken();
		switch (peek.kind)
		{
		case TOK_LEFT_BRACKET:
			nextToken();
			Term* indexPtr = newTerm(parseTerm());
			expect(TOK_RIGHT_BRACKET);
			post = (Term){SUBSCRIPT, {.subscript = {newTerm(post), indexPtr}}, s};
			break;
		case TOK_LEFT_PAREN:
			nextToken();
			if (peekToken().kind == TOK_RIGHT_PAREN)
			{
				nextToken();
				post = (Term){APPLICATION, {.app = {newTerm(post), NULL, 0}}, s};
			}
			else
			{
				list = parseArgList();
				expect(TOK_RIGHT_PAREN);
				post = (Term){APPLICATION, {.app = {newTerm(post), (Term*)list.items, (int)list.count}}, s};
			}
			break;
		// TODO: Where to add auto-dereferincg?
		case TOK_DOT:
			nextToken();
			Token ident = expect(TOK_IDENTIFIER);
			post = (Term){ACCESS, {.access = {newTerm(post), ident.start, ident.len}}, s};
			break;
		// TODO: How to hanlde other numeric types?
		case TOK_INCREMENT:
			nextToken();
			Term* constant1 = (Term*)malloc(sizeof(Term));
			*constant1 = (Term){CONSTANT,
			                    {
			                        .constant = {{.i32Val = 1}, {I32, {0}}},
			                    },
			                    s};
			post = (Term){BINARY_OP_ASSIGN, {.binAssignOp = {ADD, newTerm(post), constant1}}, s};
		// TODO: OTther numeric types.
		case TOK_DECREMENT:
			nextToken();
			Term* constantneg1 = (Term*)malloc(sizeof(Term));
			*constantneg1 = (Term){CONSTANT,
			                       {
			                           .constant = {{.i32Val = -1}, {I32, {0}}},
			                       },
			                       s};
			post = (Term){BINARY_OP_ASSIGN, {.binAssignOp = {ADD, newTerm(post), constantneg1}}, s};
		case TOK_STAR:
			nextToken();
			post = (Term){DEREF, {.deref = {newTerm(post)}}, s};
		default:
			return post;
		}
	}
}

Term parseTermFactor(void)
{
	Token recBinderOpt = (Token){TOK_IDENTIFIER, NULL, 0, -1};
	DynArray arr;
	Token tok = nextToken();
	ScopeData* scopeData;
	SourceInfo s = (SourceInfo){tok.line};

	switch (tok.kind)
	{
	case TOK_IDENTIFIER:
		scopeData = lookup(tok.start, tok.len);
		if (!scopeData)
		{
			logFatal("Undefined variable %.*s in line %d.", tok.len, tok.start, tok.line);
		}
		if (peekToken().kind == TOK_LEFT_PAREN)
		{
			nextToken();
			arr = initArray(2, sizeof(Term));
			while (peekToken().kind != TOK_RIGHT_PAREN)
			{
				appendArray(&arr, newTerm(parseTerm(0)));
				if (peekToken().kind != TOK_RIGHT_PAREN)
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
	case TOK_AMPERSAND:
		return (Term){REF, {.ref = {newTerm(parseTerm(0))}}, s};

	case TOK_LEFT_PAREN:
	{
		Term t = parseTerm(0);
		expectElse(TOK_RIGHT_PAREN, "Parentheted expression requires a closing parenthese.");
		return t;
	}
	case TOK_LEFT_BRACE:
		if (peekToken().kind == TOK_RIGHT_BRACE)
		{
			nextToken();
			return (Term){BLOCK, {.block = {.stmts = NULL, ._stmtCount = 0}}, s};
		}
		enterScope();
		arr = initArray(16, sizeof(Statement));
		Term* trailingExp = NULL;
		while (peekToken().kind != TOK_RIGHT_BRACE)
		{
			Token peek = peekToken();
			if (peek.kind == TOK_VAL || peek.kind == TOK_VAR)
			{
				DeclarationData decl = parseDeclaration();
				declare(decl.name, decl._len, decl.mutable);
				Statement newS = (Statement){DECLARATION, {.declaration = decl}, s};
				appendArray(&arr, (void*)&newS);
			}
			else
			{
				Term expr = parseTerm(0);
				if (peekToken().kind == TOK_SEMICOLON)
				{
					nextToken();
					Statement newS = (Statement){UNIT_EXPRESSION, {.unit_expression = expr}, s};
					appendArray(&arr, (void*)&newS);
				}
				else if (peekToken().kind == TOK_RIGHT_BRACE)
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
		leaveScope();
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
		return (Term){RETURN, {.retur = {newTerm(parseTerm(0))}}, s};
	case TOK_BREAK:
		return (Term){BREAK, {0}, s};
	case TOK_CONTINUE:
		return (Term){CONTINUE, {0}, s};
	case TOK_FUN:
		enterScope();
		arr = initArray(2, sizeof(Formal));
		if (peekToken().kind == TOK_IDENTIFIER)
		{
			recBinderOpt = nextToken();
		}
		if (peekToken().kind == TOK_LEFT_PAREN)
		{
			nextToken();
			while (peekToken().kind != TOK_RIGHT_PAREN)
			{
				Token name = nextToken();
				if (name.kind != TOK_IDENTIFIER)
				{
					logFatal("Expected identifier in formals list.");
				}
				Type* t = NULL;
				if (peekToken().kind == TOK_COLON)
				{
					nextToken();
					t = newType(parseType());
				}
				Formal formal = (Formal){.name = name.start, ._len = name.len, .type = t};
				appendArray(&arr, (void*)&formal);
				declare(name.start, name.len, false);
				Token peek = peekToken();
				if (peek.kind == TOK_COMMA)
				{
					nextToken();
				}
				else if (peek.kind == TOK_RIGHT_PAREN)
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
			logFatal("%i: Expected formals list or recursive bind but got %d", tok.line, tok.kind);
		}
		expect(TOK_ARROW);
		Term* t = newTerm(parseTerm(0));
		leaveScope();
		return (Term){FUNCTION,
		              {.fun =
		                   {
		                       recBinderOpt.start,
		                       recBinderOpt.len,
		                       (Formal*)arr.items,
		                       (int)arr.count,
		                       t,
		                   }},
		              s};
	default:
		logFatal("Unparseable term starting with %d.", tok.kind);
	}
	UNREACHABLE
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
	// Non-existent binary op
	default:
		abort();
	}
}

int precedence(TokenKind k)
{
	switch (k)
	{
	case TOK_DOT:
	case TOK_DOT_STAR:
		return 15;
	case TOK_AS:
		return 7;
	case TOK_COLON:
		return 6;
	case TOK_STAR:
	case TOK_SLASH:
	case TOK_PERCENT:
		return 5;
	case TOK_PLUS:
	case TOK_MINUS:
		return 4;
	case TOK_AND:
		return 3;
	case TOK_OR:
		return 2;
	case TOK_EQUAL:
		return 1;
	default:
		return -1;
	}
}

Term parseTerm()
{
	Term term = parseTermFactor();
	Token next;
	int prec;
	next = peekToken();
	prec = precedence(next.kind);
	while (prec >= minPrec)
	{
		SourceInfo s = term.info;
		// parses left-to-rigth associatively
		// TODO: differnet kind of associativities
		switch (next.kind)
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
			BinaryOpKind binOp = tokToBinOp(next.kind);
			term = (Term){BINARY_OP, {.binOp = {binOp, newTerm(term), newTerm(parseTerm(prec + 1))}}, s};
			break;

		case TOK_AS:
			nextToken();
			term = (Term){CAST, {.cast = {newTerm(term), parseType()}}, s};
			break;

		case TOK_COLON:
			nextToken();
			term = (Term){TYPED, {.typed = {newTerm(term), parseType()}}, s};
			break;

		case TOK_EQUAL:
			nextToken();
			ScopeData* varData;
			switch (term.kind)
			{
			case VAR:
				varData = lookup(term.data.var.name, term.data.var._len);
				if (!varData->mutable)
				{
					logFatal("Can not assign to immutable variable.");
				}
			// TODO: Implement assignment to a dereference: x.* = 10 ... x.*.*.* = "it goes on forever"
			default:
				logFatal("Invalid assignment, assignment to dereference not yet implemented.");
			}
			term = (Term){ASSIGNMENT, {.assignment = {newTerm(term), newTerm(parseTerm(prec + 1))}}, s};
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
		next = peekToken();
		prec = precedence(next.kind);
	}
	return term;
}

DeclarationData parseDeclaration(void)
{
	bool mutable = nextToken().kind == TOK_VAL ? false : true;
	Token ident = expectElse(TOK_IDENTIFIER, "Declaration keyword must be followed by identfier.");
	Type* typePtr = NULL;
	if (peekToken().kind == TOK_COLON)
	{
		nextToken();
		typePtr = newType(parseType());
	}
	Term* exp = NULL;
	if (peekToken().kind == TOK_EQUAL)
	{
		nextToken();
		exp = newTerm(parseTerm(0));
	}
	expectElse(TOK_SEMICOLON, "Unterminated declaration.");
	DeclarationData d = (DeclarationData){
	    .mutable = mutable,
	    .name = ident.start,
	    .type = typePtr,
	    ._len = ident.len,
	    .exp = exp,
	};
	printDeclaration(&d);
	printf("\n");
	return d;
}

#define equal(a, lit) memcmp(a.start, lit, (size_t)a.len) == 0
Type parseType(void)
{
	Token tok = nextToken();
	switch (tok.kind)
	{
	case TOK_IDENTIFIER:
		if (equal(tok, "i8"))
			return (Type){I8, {0}};
		else if (equal(tok, "i16"))
			return (Type){I16, {0}};
		else if (equal(tok, "i32"))
			return (Type){I32, {0}};
		else if (equal(tok, "i64"))
			return (Type){I64, {0}};

		else if (equal(tok, "u8"))
			return (Type){U8, {0}};
		else if (equal(tok, "u16"))
			return (Type){U16, {0}};
		else if (equal(tok, "u32"))
			return (Type){U32, {0}};
		else if (equal(tok, "u64"))
			return (Type){U64, {0}};

		else if (equal(tok, "f32"))
			return (Type){F32, {0}};
		else if (equal(tok, "f64"))
			return (Type){F64, {0}};

		Type def = mapGet(&typeDefinitions, tok.start, tok.len);
		break;

	default:
		logFatal("Unrecognized type: %s", tok.start);
		abort();
	}
}

Program parse(char* source)
{
	mapInit(&typeDefinitions);

	initLexer(source);
	enterScope();

	Token next = peekToken();
	DynArray declarations = initArray(16, sizeof(DeclarationData));
	while (next.kind != TOK_EOF)
	{
		DeclarationData newDecl = {0};
		switch (next.kind)
		{
		case TOK_VAL:
		case TOK_VAR:
			newDecl = parseDeclaration();
			declare(newDecl.name, newDecl._len, newDecl.mutable);
			appendArray(&declarations, (void*)&newDecl);
			break;
		case TOK_TYPE:
		{
		}
			nextToken();
			Token ident = nextToken();
			if (nextToken().kind != TOK_EQUAL)
			{
				logFatal("Type definitions misses equal sign after identifier.");
			}
			Type* type = newType(parseType());
			expect(TOK_SEMICOLON);
			mapPut(&typeDefinitions, ident.start, ident.len, (void*)type);
			break;

		default:
			logFatal("Expected start of declaration at line %d, but got %d", next.line, next.kind);
			break;
		}
		next = peekToken();
		printScope();
	}
	leaveScope();
	return (Program){(DeclarationData*)declarations.items, (int)declarations.count};
}

#endif
