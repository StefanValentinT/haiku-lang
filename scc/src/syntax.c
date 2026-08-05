#ifndef SYNTAX_H
#define SYNTAX_H

#include <stdbool.h>
#include <stdint.h>

// The AST definition
// Fields prefixed with an underscore indicate
// that the field is not part of the Abstract Syntax
// but merely there for implementation reasons
// (e. g. we always store the length of a string together with the string)

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
	F16,
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
	BUILTIN_VAR,
	REF,
	DEREF,
	CAST,
	TYPED,
	RETURN,
	BREAK,    // no data
	CONTINUE, // no data
	APPLICATION,
	FUNCTION,
	ASSIGNMENT,
	BLOCK
} TermKind;

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
} ArrayData;

typedef struct
{
	char* string;
	int _len;
} StringData;

typedef struct
{
	char* name;
	int _len;
} VarData;

typedef struct
{
	char* name;
	int _len;
} BuiltinVarData;

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

// TODO: Have application of anonymous functions be syntactic sugar.
// (fun (x) -> x)(1) becomes apply(fun (x) -> x, 1)
// where apply = fun (f, arg...)
// Or maybe somehting else?
typedef struct
{
	char* funName;
	int _len;
	Term* args;
	int _argCount;
} ApplicationData;

typedef struct
{
	char* name;
	int _len;
	Type* type; // nullable
} Formal;

typedef struct
{
	char* recBinder; // nullable
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
		BuiltinVarData builtinVar;

		RefData ref;
		DerefData deref;
		CastData cast;

		TypedData typed;
		ReturnData retur;

		ApplicationData app;
		FunctionData fun;

		AssignmentData assignment;
		BlockData block;
	} data;
};

// Statements

typedef struct
{
	char* name;
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
};

// Whole Program

typedef DeclarationData* Program;

Term* newTerm(Term t);

#endif
#if __INCLUDE_LEVEL__ == 0

#include "log.c"
#include <stdlib.h>

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

Statement* newStatement(Statement t)
{
	Statement* ptr = malloc(sizeof(Term));
	if (ptr == NULL)
	{
		logFatal("Could not allocate enough memory to make an AST Node.");
	}
	*ptr = t;
	return ptr;
}

#endif
