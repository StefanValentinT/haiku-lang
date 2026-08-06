#ifndef PARSER_H
#define PARSER_H

#include "syntax.c"

Program parse(char* source);

#endif
#if __INCLUDE_LEVEL__ == 0

#include "lexer.c"
#include "log.c"
#include "stdlib.h"

bool hadError;
bool inPanicMode;

DeclarationData parseDeclaration(bool mutable)
{
	return (DeclarationData){
	    .mutable = mutable,
	    .name = "stub",
	    ._len = 4,
	    .exp = NULL,
	    .info = (SourceInfo){5},
	};
}

Program parse(char* source)
{
	initLexer(source);
	Token tok = lexToken();

	int capacity = 8;
	int count = 0;
	DeclarationData* declarations =
	    malloc((size_t)capacity * sizeof(DeclarationData));

	while (tok.type != TOK_EOF)
	{
		DeclarationData newDecl = {0};
		switch (tok.type)
		{
		case TOK_VAL:
			newDecl = parseDeclaration(false);
			break;
		case TOK_VAR:
			newDecl = parseDeclaration(true);
			break;
		default:
			logError("Epxected start of declaration at %d.", tok.line);
		}
		if (count >= capacity)
		{
			capacity = capacity * 2;
			DeclarationData* temp = realloc(
			    declarations, (size_t)capacity * sizeof(DeclarationData)
			);
			if (temp == NULL)
			{
				logFatal("Could not allocate enough memory to parse all "
				         "declarations.");
			}
			declarations = temp;
		}
		declarations[count] = newDecl;
		count++;
		tok = lexToken();
	}
}

#endif
