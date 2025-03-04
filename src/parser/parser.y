%{

#include <stdlib.h>
#include <assert.h>

#include "parser.h"

%}

%parse-param { FILE* fp }

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
	tree_t *tval;

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
%type <type_val> type
%type <type_val> standard_type

%type <lname_val> arguments
%type <lname_val> parameter_list
%type <lname_val> declarations
%type <lname_val> subprogram_declarations

%%

program
	: PROGRAM OPEN_P identifier_list CLOSE_P SEMICOLON
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
	: declarations VAR identifier_list COLON type SEMICOLON
	| /* empty */
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
	: subprogram_declarations subprogram_declaration SEMICOLON
	| /* empty */
	;

subprogram_declaration
	: subprogram_header
	| declarations
	| subprogram_declarations
	| compound_statement
	;

subprogram_header
	: FUNCTION NAME arguments COLON standard_type SEMICOLON
	| PROCEDURE NAME arguments SEMICOLON
	;

arguments
	: OPEN_P parameter_list CLOSE_P
	| /* empty */
	;

parameter_list
	: identifier_list COLON type
	| parameter_list SEMICOLON identifier_list COLON type
	;

compound_statement
	: BBEGIN optional_statements END
	;

optional_statements
	: statement_list
	| /* empty */
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
	| NAME OPEN_P expression_list CLOSE_P
	| NAME OPEN_B expression CLOSE_B
	| INUM DOT
	| OPEN_P expression CLOSE_P
	| NOT factor
	;

%%

int parse(const char *file_path)
{
	FILE* file = fopen(file_path, "a");
	if(file == NULL)
	{
		printf("[ERROR] %s not found\n, file_path");
		return 1;
	}
	scope_t scope;
	int out = yyparse(file);
	fclose(file);
	return out;
}
