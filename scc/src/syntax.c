#ifndef SYNTAX_H
#define SYNTAX_H

#include "dynarray.c"
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

typedef struct
{
	bool isAuto;
	union
	{
		u64 intData;
		struct
		{
			const char* charData;
			size length;
		} stringData;
	} data;
} identifier;

typedef struct
{
	const char* chars;
	size length;
} string;

identifier newIdent(void);
identifier makeIdent(const char* content, size length);
bool isEqualIdent(const identifier* id1, const identifier* id2);
u64 toAutoID(const identifier* id);
string toString(const identifier* id);
void printIdent(identifier ident);

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
	STRUCT_TYPE,
} TypeKind;

typedef struct Type Type;

typedef struct
{
	Type* elemType;
	size* elemCount; // nullable
} ArrayTypeData;

typedef struct
{
	Type* paramTypes;
	size _paramCount;
	Type* retType;
} FunTypeData;

typedef struct
{
	identifier name;
	Type* type;
} MemberType;

typedef struct
{
	MemberType* memberTypes;
	size _memberCount;
	bool isUnion;
} StructTypeData;

struct Type
{
	TypeKind kind;
	union
	{
		ArrayTypeData arr;
		FunTypeData fun;
		StructTypeData structure;
	} data;
};

// Terms

typedef enum
{
	CONSTANT,
	ARRAY,
	STRUCTURE,
	STRING,
	VAR,
	REF,
	DEREF,
	CAST,
	TYPED,
	RETURN,
	BREAK,    // no data
	CONTINUE, // no data
	UNARY_OP,
	BINARY_OP,
	BINARY_OP_ASSIGN,
	SUBSCRIPT,
	ACCESS,
	CONDITIONAL,
	LOOP,
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

	EQUAL,
	NOT_EQUAL,
	LESS_THAN,
	LESS_OR_EQUAL,
	GREATER_THAN,
	GREATER_OR_EQUAL,

	AND,
	OR,
} BinaryOpKind;

typedef enum
{
	BIT_NOT,
	NOT,
	NEG,
	POST_INCREMENT,
	POST_DECREMENT,
	PRE_INCREMENT,
	PRE_DECREMENT,
} UnaryOpKind;

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
		i8 i8Val;
		i16 i16Val;
		i32 i32Val;
		i64 i64Val;
		u8 u8Val;
		u16 u16Val;
		u32 u32Val;
		u64 u64Val;
		float f32Val;
		double f64Val;
	} data;
	Type numericType;
} ConstantData;

typedef struct
{
	ConstantData* constants;
	size _constantsCount;
} ArrayData;

typedef struct
{
	identifier name;
	Term* term;
} Member;

typedef struct
{
	bool isUnion;
	Member* members;
	size memberCount;
} StructData;

typedef struct
{
	identifier string;
} StringData;

typedef struct
{
	identifier name;
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

// a *= val
typedef struct
{
	BinaryOpKind kind;
	Term* a;
	Term* value;
} BinOpAssignData;

typedef struct
{
	UnaryOpKind kind;
	Term* t;
} UnOpData;

typedef struct
{
	Term* term;
	Term* index;
} SubscriptData;

typedef struct
{
	Term* term;
	identifier member;
} AccessData;

typedef struct
{
	Term* cond;
	Term* ifBranch;
	Term* thenBranch; // nullable
} ConditionalData;

typedef struct
{
	Term* cond;
	Term* body;
} LoopData;

typedef struct
{
	Term* fun;
	Term* args;
	int _argCount;
} ApplicationData;

typedef struct
{
	identifier name;
	Type* type; // nullable
} Formal;

typedef struct
{
	identifier recBinder;
	Formal* formals;
	size _formalCount;
	Type* retType; // nullable
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
	size _stmtCount;
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
		StructData structure;

		VarData var;

		RefData ref;
		DerefData deref;
		CastData cast;

		TypedData typed;
		ReturnData retur;

		BinOpData binOp;
		BinOpAssignData binAssignOp;
		UnOpData unOp;
		SubscriptData subscript;
		AccessData access;

		ConditionalData cond;
		LoopData loop;

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
	identifier name;
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
	size _declCount;
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
#include <string.h>

identifier newIdent(void)
{
	static u64 identCount = 0;
	identifier ident = (identifier){true, {.intData = identCount++}};
	return ident;
}

identifier makeIdent(const char* content, size_t length)
{
	identifier id = {false, {.stringData = {content, length}}};
	return id;
}

bool isEqualIdent(const identifier* id1, const identifier* id2)
{
	if (id1->isAuto != id2->isAuto)
	{
		return false;
	}
	if (id1->isAuto)
	{
		return id1->data.intData == id2->data.intData;
	}
	else
	{
		if (id1->data.stringData.length != id2->data.stringData.length)
		{
			return false;
		}
		return memcmp(
		           id1->data.stringData.charData, id2->data.stringData.charData,
		           id1->data.stringData.length
		       ) == 0;
	}
}

u64 toAutoID(const identifier* id) { return id->data.intData; }

string toString(const identifier* id)
{
	return (string){id->data.stringData.charData, id->data.stringData.length};
}

void printIdent(identifier ident)
{
	if (ident.isAuto)
	{
		printf("auto#%" PRIuPTR, (uintptr_t)ident.data.intData);
	}
	else
	{
		printf("%.*s", (int)ident.data.stringData.length, ident.data.stringData.charData);
	}
}

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
		printf("of size %" PRIuPTR ")", *t->data.arr.elemCount);
		break;
	case FUN_TYPE:
		printf("(FUN_TYPE ");
		for (size i = 0; i < t->data.fun._paramCount; i++)
		{
			printType(&t->data.fun.paramTypes[i]);
			printf(" ");
		}
		printf("->");
		printType(t->data.fun.retType);
		printf(")");
		break;
	case STRUCT_TYPE:
		if (t->data.structure.isUnion)
		{
			printf("(UNION ");
		}
		else
		{
			printf("(STRUCT ");
		}
		for (size i = 0; i < t->data.structure._memberCount; i++)
		{
			MemberType m = t->data.structure.memberTypes[i];
			printIdent(m.name);
			printf(": ");
			printType(m.type);
		}
		printf(")");
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
	for (size i = 0; i < a->_constantsCount; i++)
	{
		printConstant(&a->constants[i]);
	}
	printf(")");
}

void printStructure(const StructData* s)
{
	if (s->isUnion)
	{
		printf("(UNION ");
	}
	else
	{
		printf("(STRUCT ");
	}
	for (size i = 0; i < s->memberCount; i++)
	{
		Member m = s->members[i];
		printIdent(m.name);
		printf(": ");
		printTerm(m.term);
	}
	printf(")");
}

void printString(const StringData* s)
{
	printf("\"");
	printIdent(s->string);
	printf("\"");
}

void printVar(const VarData* s) { printIdent(s->name); }

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

const char* binOpToString(BinaryOpKind b)
{
	switch (b)
	{
	case ADD:
		return "ADD";
	case SUBTRACT:
		return "SUBTRACT";
	case MULTIPLY:
		return "MULTIPLY";
	case DIVIDE:
		return "DIVIDE";
	case REMAINDER:
		return "REMAINDER";
	case EQUAL:
		return "EQUAL";
		break;
	case NOT_EQUAL:
		return "NOT-EQUAL";
		break;
	case LESS_THAN:
		return "LT";
		break;
	case LESS_OR_EQUAL:
		return "LE";
		break;
	case GREATER_THAN:
		return "GT";
		break;
	case GREATER_OR_EQUAL:
		return "GE";
		break;
	case AND:
		return "AND";
	case OR:
		return "OR";
	}
}

void printBinaryOp(const BinOpData* b)
{
	printf("(%s ", binOpToString(b->kind));
	printTerm(b->a);
	printf(" ");
	printTerm(b->b);
	printf(")");
}

void printBinaryOpAssign(const BinOpAssignData* b)
{
	printf("(%s-ASSIGN ", binOpToString(b->kind));
	printTerm(b->a);
	printf(" ");
	printTerm(b->value);
	printf(")");
}

void printUnaryOp(const UnOpData* u)
{
	printf("(");
	switch (u->kind)
	{
	case PRE_DECREMENT:
		printf("PRE-DECREMENT");
		break;
	case PRE_INCREMENT:
		printf("PRE-INCREMENT");
		break;
	case POST_INCREMENT:
		printf("POST-INCREMENT");
		break;
	case POST_DECREMENT:
		printf("POST-DECREMENT");
		break;
	case NOT:
		printf("NOT");
		break;
	case BIT_NOT:
		printf("BIT-NOT");
		break;
	case NEG:
		printf("-");
	}
	printf(" ");
	printTerm(u->t);
	printf(")");
}

void printApplication(const ApplicationData* a)
{
	printf("(APP (");
	printTerm(a->fun);
	printf(") ");
	for (int i = 0; i < a->_argCount; i++)
	{
		printTerm(&a->args[i]);
		if (i < a->_argCount - 1)
		{
			printf(" ");
		}
	}
	printf(")");
}

void printFunction(const FunctionData* f)
{
	printf("(FUNCTION ");
	printIdent(f->recBinder);
	printf("(");
	for (size i = 0; i < f->_formalCount; i++)
	{
		Formal form = f->formals[i];
		printIdent(form.name);
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
	printf(")");
	if (f->retType != NULL)
	{
		printf(" ");
		printType(f->retType);
	}
	printf(" -> ");
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

static int level = 0;

void indent(int n)
{
	if (n == 0)
		return;
	printf("    ");
	indent(n - 1);
}

void printBlock(const BlockData* b)
{
	printf("(BLOCK \n");
	level++;
	for (size i = 0; i < b->_stmtCount; i++)
	{
		indent(level);
		printStatement(&b->stmts[i]);
		printf("\n");
	}
	if (b->exp != NULL)
	{
		indent(level);
		printTerm(b->exp);
		printf("\n");
	}
	level--;
	indent(level);
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
	case STRUCTURE:
		printStructure(&t->data.structure);
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
	case BINARY_OP_ASSIGN:
		printBinaryOpAssign(&t->data.binAssignOp);
		break;
	case UNARY_OP:
		printUnaryOp(&t->data.unOp);
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
	// TODO: Still have to add a few cases, hopefully the last ones
	case SUBSCRIPT:
		printf("(TODO SUBSCRIPT)");
		break;
	case ACCESS:
		printf("(TODO ACCESS)");
		break;
	case CONDITIONAL:
		printf("(TODO CONDITIONAL)");
		break;
	case LOOP:
		printf("(TODO LOOP)");
		break;
	}
}

void printDeclaration(const DeclarationData* d)
{
	if (d->mutable)
	{
		printf("(VAR ");
	}
	else
	{
		printf("(VAR ");
	}
	printIdent(d->name);
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
	for (size i = 0; i < p->_declCount; i++)
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
