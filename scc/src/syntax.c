#ifndef SYNTAX_H
#define SYNTAX_H

#include "lexer.c"
#include <stdbool.h>
#include <stdint.h>

// The AST definition
// Fields prefixed with an underscore indicate
// that the field is not part of the Abstract Syntax
// but merely there for implementation reasons
// (e. g. we always store the length of a string together with the string)

typedef struct
{
	int line;
} SourceInfo;

// Types

typedef enum
{
	I8,
	I16,
	I32,
	I64,
	U8,
	U16,
	U32,
	U64,
	F32,
	F64,
	ARRAY_TYPE,
	FUN_TYPE,
} TypeKind;

typedef struct Type Type;

typedef struct
{
	Type* elemType;
	int* elemCount; // nullable
} ArrayTypeData;

typedef struct
{
	Type* paramTypes;
	int _paramCount;
	Type* retType;
} FunTypeData;

struct Type
{
	TypeKind kind;
	union
	{
		ArrayTypeData arr;
		FunTypeData fun;
	} data;
};

// Terms

typedef enum
{
	CONSTANT,
	ARRAY,
	STRING,
	VAR,
	REF,
	DEREF,
	CAST,
	TYPED,
	RETURN,
	BREAK,    // no data
	CONTINUE, // no data
	BINARY_OP,
	APPLICATION,
	FUNCTION,
	ASSIGNMENT,
	BLOCK
} TermKind;

typedef enum
{
	ADD,
	SUBTRACT,
	MULTIPLY,
	DIVIDE,
	REMAINDER,
	AND,
	OR,
} BinaryOpKind;

typedef enum
{
	DECLARATION,
	UNIT_EXPRESSION
} StatementKind;

typedef struct Term Term;
typedef struct Statement Statement;

typedef struct
{
	union
	{
		int8_t i8Val;
		int16_t i16Val;
		int32_t i32Val;
		int64_t i64Val;
		uint8_t u8Val;
		uint16_t u16Val;
		uint32_t u32Val;
		uint64_t u64Val;
		float f32Val;
		double f64Val;
	} data;
	Type numericType;
} ConstantData;

typedef struct
{
	ConstantData* constants;
	int _constantsCount;
} ArrayData;

typedef struct
{
	const char* string;
	int _len;
} StringData;

typedef struct
{
	const char* name;
	int _len;
} VarData;

typedef struct
{
	Term* exp;
} RefData;

typedef struct
{
	Term* exp;
} DerefData;

typedef struct
{
	Term* exp;
	Type type;
} CastData;

typedef struct
{
	Term* exp;
	Type type;
} TypedData;

typedef struct
{
	Term* exp; // nullable
} ReturnData;

typedef struct
{
	BinaryOpKind kind;
	Term* a;
	Term* b;
} BinOpData;

// TODO: Have application of anonymous functions be syntactic sugar.
// (fun (x) -> x)(1) becomes apply(fun (x) -> x, 1)
// where apply = fun (f, arg...)
// Or maybe somehting else?
typedef struct
{
	const char* funName;
	int _len;
	Term* args;
	int _argCount;
} ApplicationData;

typedef struct
{
	const char* name;
	int _len;
	Type* type; // nullable
} Formal;

typedef struct
{
	const char* recBinder; // nullable
	int _recBinderLength;
	Formal* formals;
	int _formalCount;
	Term* body;
} FunctionData;

typedef struct
{
	Term* lvalue;
	Term* value;
} AssignmentData;

typedef struct
{
	Statement* stmts;
	int _stmtCount;
	Term* exp; // nullable
} BlockData;

struct Term
{
	TermKind kind;
	union
	{
		ConstantData constant;
		ArrayData array;
		StringData string;

		VarData var;

		RefData ref;
		DerefData deref;
		CastData cast;

		TypedData typed;
		ReturnData retur;

		BinOpData binOp;
		ApplicationData app;
		FunctionData fun;

		AssignmentData assignment;
		BlockData block;
	} data;
	SourceInfo info;
};

// Statements

typedef struct
{
	const char* name;
	int _len;
	Type* type; // nullable
	bool mutable;
	Term* exp; // nullable
} DeclarationData;

struct Statement
{
	StatementKind kind;
	union
	{
		DeclarationData declaration;
		Term unit_expression;
	} data;
	SourceInfo info;
};

// Whole Program

typedef struct
{
	DeclarationData* decls;
	int _declCount;
} Program;

// Allocation
Term* newTerm(Term t);
Type* newType(Type t);
Statement* newStatement(Statement s);

// Pretty printing
void printTerm(const Term* t);
void printStatement(const Statement* s);
void printProgram(const Program* p);

void printConstant(const ConstantData* t);
void printArray(const ArrayData* a);
void printString(const StringData* s);
void printVar(const VarData* s);
void printCast(const CastData* c);
void printTyped(const TypedData* c);
void printBinaryOp(const BinOpData* b);
void printApplication(const ApplicationData* a);
void printFunction(const FunctionData* f);
void printAssignment(const AssignmentData* a);
void printBlock(const BlockData* b);

void printDeclaration(const DeclarationData* d);

#endif
#if __INCLUDE_LEVEL__ == 0

#include "log.c"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

void printType(const Type* t)
{
	switch (t->kind)
	{
	case I8:
		printf("i8");
		break;
	case I16:
		printf("i16");
		break;
	case I32:
		printf("i32");
		break;
	case I64:
		printf("i64");
		break;
	case U8:
		printf("u8");
		break;
	case U16:
		printf("u16");
		break;
	case U32:
		printf("u32");
		break;
	case U64:
		printf("u64");
		break;
	case F32:
		printf("f32");
		break;
	case F64:
		printf("f64");
		break;
	case ARRAY_TYPE:
		printf("(ARRAY_TYPE ");
		printType(t->data.arr.elemType);
		printf("of size %i)", *t->data.arr.elemCount);
		break;
	case FUN_TYPE:
		printf("(FUN_TYPE ");
		for (int i = 0; i < t->data.fun._paramCount; i++)
		{
			printType(&t->data.fun.paramTypes[i]);
			printf(" ");
		}
		printf("->");
		printType(t->data.fun.retType);
		printf(")");
		break;
	}
}

void printConstant(const ConstantData* t)
{
	switch (t->numericType.kind)
	{
	case I8:
		printf("(CONSTANT %" PRId8 ")", t->data.i8Val);
		break;
	case I16:
		printf("(CONSTANT %" PRId16 ")", t->data.i16Val);
		break;
	case I32:
		printf("(CONSTANT %" PRId32 ")", t->data.i32Val);
		break;
	case I64:
		printf("(CONSTANT %" PRId64 ")", t->data.i64Val);
		break;
	case U8:
		printf("(CONSTANT %" PRIu8 ")", t->data.u8Val);
		break;
	case U16:
		printf("(CONSTANT %" PRIu16 ")", t->data.u16Val);
		break;
	case U32:
		printf("(CONSTANT %" PRIu32 ")", t->data.u32Val);
		break;
	case U64:
		printf("(CONSTANT %" PRIu64 ")", t->data.u64Val);
		break;
	case F32:
		printf("(CONSTANT %f)", t->data.f32Val);
		break;
	case F64:
		printf("(CONSTANT %lf)", t->data.f64Val);
		break;
	default:
		printf("Not a constant!");
		break;
	}
}

void printArray(const ArrayData* a)
{
	printf("(ARRAY ");
	for (int i = 0; i < a->_constantsCount; i++)
	{
		printConstant(&a->constants[i]);
	}
	printf(")");
}

void printString(const StringData* s) { printf("\"%.*s\"", s->_len, s->string); }

void printVar(const VarData* s) { printf("%.*s", s->_len, s->name); }

void printCast(const CastData* c)
{
	printf("(CAST ");
	printTerm(c->exp);
	printf(" as ");
	printType(&c->type);
	printf(")");
}

void printTyped(const TypedData* c)
{
	printf("(TYPED ");
	printTerm(c->exp);
	printf(" as ");
	printType(&c->type);
	printf(")");
}

void printBinaryOp(const BinOpData* b)
{
	switch (b->kind)
	{
	case ADD:
		printf("(ADD ");
		break;
	case SUBTRACT:
		printf("(SUBTRACT ");
		break;
	case MULTIPLY:
		printf("(MULTIPLY ");
		break;
	case DIVIDE:
		printf("(DIVIDE ");
		break;
	case REMAINDER:
		printf("(REMAINDER ");
		break;
	case AND:
		printf("(AND ");
		break;
	case OR:
		printf("(OR ");
		break;
	}
	printTerm(b->a);
	printf(" ");
	printTerm(b->b);
	printf(")");
}

void printApplication(const ApplicationData* a)
{
	printf("(APP %.*s ", a->_len, a->funName);
	for (int i = 0; i < a->_argCount; i++)
	{
		printTerm(&a->args[i]);
		printf(" ");
	}
	printf(")");
}

void printFunction(const FunctionData* f)
{
	printf("(FUNCTION %.*s", f->_recBinderLength, f->recBinder);
	printf("(");
	for (int i = 0; i < f->_formalCount; i++)
	{
		Formal form = f->formals[i];
		printf("%.*s", form._len, form.name);
		if (form.type)
		{
			printf(": ");
			printType(form.type);
		}
		if (i + 1 < f->_formalCount)
		{
			printf(", ");
		}
	}
	printf(") ");
	printTerm(f->body);
	printf(")");
}

void printAssignment(const AssignmentData* a)
{
	printf("(ASSIGN ");
	printTerm(a->lvalue);
	printf(" ");
	printTerm(a->value);
	printf(")");
}

void printBlock(const BlockData* b)
{
	printf("(BLOCK \n");
	for (int i = 0; i < b->_stmtCount; i++)
	{
		printf("    ");
		printStatement(&b->stmts[i]);
		printf("\n");
	}
	printf(")");
}

void printTerm(const Term* t)
{
	switch (t->kind)
	{
	case CONSTANT:
		printConstant(&t->data.constant);
		break;
	case ARRAY:
		printArray(&t->data.array);
		break;
	case STRING:
		printString(&t->data.string);
		break;
	case VAR:
		printVar(&t->data.var);
		break;
	case REF:
		printf("(REF ");
		printTerm(t->data.ref.exp);
		printf(")");
		break;
	case DEREF:
		printf("(DEREF ");
		printTerm(t->data.deref.exp);
		printf(")");
		break;
	case CAST:
		printCast(&t->data.cast);
		break;
	case TYPED:
		printTyped(&t->data.typed);
		break;
	case RETURN:
		printf("(RETURN ");
		printTerm(t->data.retur.exp);
		printf(")");
		break;
	case BREAK:
		printf("BREAK");
		break;
	case CONTINUE:
		printf("CONTINUE");
		break;
	case BINARY_OP:
		printBinaryOp(&t->data.binOp);
		break;
	case APPLICATION:
		printApplication(&t->data.app);
		break;
	case FUNCTION:
		printFunction(&t->data.fun);
		break;
	case ASSIGNMENT:
		printAssignment(&t->data.assignment);
		break;
	case BLOCK:
		printBlock(&t->data.block);
		break;
	}
}

void printDeclaration(const DeclarationData* d)
{
	if (d->mutable)
	{
		printf("(VAR %.*s", d->_len, d->name);
	}
	else
	{
		printf("(VAR %.*s", d->_len, d->name);
	}
	if (d->type)
	{
		printf(" : ");
		printType(d->type);
	}
	if (d->exp)
	{
		printf(" = ");
		printTerm(d->exp);
	}
	printf(")");
}

void printStatement(const Statement* stmt)
{
	switch (stmt->kind)
	{
	case DECLARATION:
		printDeclaration(&stmt->data.declaration);
		break;
	case UNIT_EXPRESSION:
		printTerm(&stmt->data.unit_expression);
		break;
	}
}

void printProgram(const Program* p)
{
	for (int i = 0; i < p->_declCount; i++)
	{
		printDeclaration(&p->decls[i]);
		printf("\n");
	}
}

Term* newTerm(Term t)
{
	Term* ptr = malloc(sizeof(Term));
	if (ptr == NULL)
	{
		logFatal("Could not allocate enough memory to make an AST Node.");
	}
	*ptr = t;
	return ptr;
}

Type* newType(Type t)
{
	Type* ptr = malloc(sizeof(Type));
	if (ptr == NULL)
	{
		logFatal("Could not allocate enough memory to make an AST Node.");
	}
	*ptr = t;
	return ptr;
}

Statement* newStatement(Statement t)
{
	Statement* ptr = malloc(sizeof(Statement));
	if (ptr == NULL)
	{
		logFatal("Could not allocate enough memory to make an AST Node.");
	}
	*ptr = t;
	return ptr;
}

#endif
