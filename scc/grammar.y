%token identifier
%token numeric-constant
%token char-constant
%token string-constant

%start program

%%

atom: identifier
	| numeric-constant
	| char-constant
	| string-constant
	;

factor: atom
	| '(' term ')'
	| "struct" '{' '}'
	| "struct" '{' init-list '}'
	| "union" '{' '}'
	| "union" '{' init-list '}'
	;

postfix: factor
	| identifier '{' '}'
	| identifier '{' init-list '}'
	| '[' '_' ']'  '{' arg-list '}'
	| '[' numeric-constant ']'  '{' arg-list '}'
	| postfix '[' term ']'
	| postfix '(' ')'
	| postfix '(' arg-list ')'
	| postfix '.' identifier
	| postfix "++"
	| postfix "--"
	| postfix ".*"
	;

arg-list: term
	| arg-list ',' term
	;

init-list: identifier '=' term
	| init-list ',' identifier '=' term
	;
	
prefix: postfix
	| unary-op prefix
	| "++" prefix
	| "--" prefix
	;
	
unary-op: '&' | '-' | '+' | '!' | '~'
	;

binary-type: prefix
	| binary-type ':' type
	| binary-type "as" type
	;

type: "i8"  | "i16" | "i32" | "i64"
	| "u8"  | "u16" | "u32" | "u64"
	| "f32" | "f64"
	| "struct" '{' '}'
	| "struct" '{' typed-list '}'
	| "union" '{' '}'
	| "union" '{' typed-list '}'
	| '[' numeric-constant ']' type
	| '(' ')' "->" type
	| '(' type-list ')' "->" type
	;

typed-list: identifier ':' type
	| typed-list ',' identifier ':' type
	;

type-list: type
	| type-list ',' type
	;

multiplicative: binary-type
	| multiplicative '*' binary-type
	| multiplicative '/' binary-type
	| multiplicative '%' binary-type
	;

additive: multiplicative
	| additive '+' multiplicative
	| additive '-' multiplicative
	;

shifting: additive
	| shifting ">>" additive
	| shifting "<<" additive
	;

relational: shifting
	| relational "==" shifting
	| relational "!=" shifting
	| relational "<=" shifting
	| relational "<" shifting
	| relational ">=" shifting
	| relational ">" shifting
	;

logical: relational
	| logical "and" relational
	| logical "or" relational
	;

control-flow: logical
	| "if" term "then" term
	| "if" term "then" term "else" term
	| "for" term "do" term
	| "break"
	| "continue"
	| "return" term
	| "defer" term
	| '{' '}'
	| '{' statement-list ';' '}'
	| '{' term '}'
	| '{' statement-list ';' term '}'
	| "fun" identifier_opt '(' ')' "->" type_opt term
	| "fun" identifier_opt '(' formals-list ')' type_opt "->" term
	;
	
formal: identifier
	| identifier ':' type
	;

formals-list: formal
	| formals-list ',' formal
	;

assignment: control-flow
	| postfix '=' assignment
	;

term: assignment
	;

declaration: "val" identifier '=' term
	| "val" identifier ':' type '=' term
	| "var" identifier '=' term
	| "var" identifier ':' type '=' term
	;
	
statement: control-flow | declaration
	;

statement-list: statement
	| statement-list ';' statement
	;

declaration-list: declaration
	| declaration ';' declaration
	;

program: declaration-list
	;

%%
