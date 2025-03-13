%{

#include <stdlib.h>
#include <assert.h>

#include "parser.h"

extern FILE *yyin;
scope_t* scope;
size_t scope_depth = 0;

%}

%union
{
	/*
	 *	scanner fields
	 */

	// INUM value
	int ival;

	// RNUM value
	float rval;

	// RELOP ADDOP MULOP value
	int opval;

	// NAME value
	char *sval;

	/*
	 *	semantic fields
	 */

	// syntax tree value
	syntax_tree_t *tval;

	// type value
	ptype_t *type_val;

	// type list
	ltype_t *ltype_val;

	// name list
	lname_t *lname_val;
}

%token PROGRAM FUNCTION PROCEDURE
%token VAR ARRAY OF
%token INTEGER REAL
%token BBEGIN END
%token IF THEN ELSE
%token WHILE DO
%token REPEAT UNTIL
%token FOR TO

%token <ival> INUM
%token <rval> RNUM
%token <sval> NAME

%token <opval> RELOP
%token <opval> ADDOP
%token <opval> MULOP

%token LT LE GT GE EQ NE
%token PLUS MINUS OR
%token STAR SLASH MOD DIV AND
%token NOT
%token ASSOP
%token DOTOP

%token COMMA LOCAL PARAMETER

%token OPEN_P CLOSE_P
%token OPEN_B CLOSE_B
%token SEMICOLON COLON DOT

%token ERR

%type <tval> compound_statement
%type <tval> optional_statements
%type <tval> statement_list
%type <tval> statement
%type <tval> variable
%type <tval> procedure_statement

%type <tval> expression_list
%type <tval> expression
%type <tval> simple_expression
%type <tval> term
%type <tval> factor

%type <tval> identifier_list
%type <tval> type
%type <tval> standard_type

%type <tval> arguments
%type <tval> parameter_list
%type <tval> declarations
%type <tval> subprogram_declarations

%%

program
	: PROGRAM NAME OPEN_P identifier_list CLOSE_P SEMICOLON
	declarations
	subprogram_declarations
	compound_statement
	DOT
	;

identifier_list
	: NAME
	| identifier_list COMMA NAME
	;

declarations
	: /* empty */
	| declarations VAR identifier_list COLON type SEMICOLON
	;

type
	: standard_type
	| ARRAY OPEN_B range CLOSE_B OF standard_type
	;

range
	: INUM DOTOP INUM
	;

standard_type
	: INTEGER
	| REAL
	;

subprogram_declarations
	: /* empty */
	| subprogram_declarations subprogram_declaration SEMICOLON
	;

subprogram_declaration
	: subprogram_header
		declarations
		subprogram_declarations
		compound_statement
	;

subprogram_header
	: FUNCTION NAME arguments COLON standard_type SEMICOLON
	| PROCEDURE NAME arguments SEMICOLON
	;

arguments
	: /* empty */
	| OPEN_P parameter_list CLOSE_P
	;

parameter_list
	: identifier_list COLON type
	| parameter_list SEMICOLON identifier_list COLON type
	;

compound_statement
	: BBEGIN optional_statements END
	;

optional_statements
	: /* empty */
	| statement_list
	;

statement_list
	: statement
	| statement_list SEMICOLON statement
	;

statement
	: variable ASSOP expression
	| procedure_statement
	| compound_statement
	| IF expression THEN statement ELSE statement
	| IF expression THEN statement
	| WHILE expression DO statement
	| REPEAT statement UNTIL expression
	| FOR NAME ASSOP range DO statement
	| FOR NAME ASSOP INUM TO INUM DO statement
	;

variable
	: NAME
	| NAME OPEN_B expression CLOSE_B
	;

procedure_statement
	: NAME
	| NAME OPEN_P expression_list CLOSE_P
	;

expression_list
	: expression
	| expression_list COMMA expression
	;

expression
	: simple_expression
	| simple_expression RELOP simple_expression
	;

simple_expression
	: term
	| ADDOP term
	| simple_expression ADDOP term
	;

term
	: factor
	| term MULOP factor
	;

factor
	: NAME
		{ $$ = tree_sym( search_scope_depth( scope, $1, scope_depth ) ); }
	| NAME OPEN_P expression_list CLOSE_P
		{ $$ = tree_op( FUNCTION_T, tree_sym( search_scope( scope, $1 ) ), $3 ); }
	| NAME OPEN_B expression CLOSE_B
		{ $$ = tree_op( ARRAY_T, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 ); }
	| INUM
		{ $$ = tree_inum( $1 ); }
	| RNUM
		{ $$ = tree_rnum( $1 ); }
	| OPEN_P expression CLOSE_P
		{ $$ = $2; }
	| NOT factor
		{ $$ = tree_op( NOT_T, $2, NULL ); }
	;

%%

int parse(const char *file_path)
{
	yyin = fopen(file_path, "r");
	if(yyin == NULL)
	{
		fprintf(stderr, "[ERROR] %s not found\n", file_path);
		return 1;
	}

	scope = make_scope();

	int out = yyparse();
	fclose(yyin);

	(void)free_scope(scope);

	return out;
}
