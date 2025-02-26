%{

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"

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

%token ERR

%type <tval> compound_statement
%type <tval> optional_statement
%type <tval> statement_list
%type <tval> statement
%type <tval> matched_statement
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
%type <lname_val> paramerter_list
%type <lname_val> declarations

%%

program
	:
	;

%%

int parse(void)
{
	scope_t scope;
	return yyparse();
}
