%{

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"
#include "tree.h"

#define NUM 256
#define ID 257

%}

number		[0-9]+
floating	[0-9]*"."[0-9]+
ident		[_a-zA-Z][_a-zA-Z0-9]*
whitespace	[ \t]+

%%

"program"		{ return PROGAM; }
"procedure"		{ return PROCEDURE; }
"function"		{ return FUNCTION; }
"var"			{ return VAR; }
"array"			{ return ARRAY; }
"of"			{ return OF; }
"begin"			{ return BBEGIN; }
"end"			{ return END; }
"integer"		{ return INTEGER; }
"real"			{ return REAL; }
"if"			{ return IF; }
"then"			{ return THEN; }
"else"			{ return ELSE; }
"while"			{ return WHILE; }
"do"			{ return DO; }
"for"			{ return FOR; }
"to"			{ return TO; }

"<"				{ return RELOP; }
"<="			{ return RELOP; }
">"				{ return RELOP; }
">="			{ return RELOP; }
"="				{ return RELOP; }
"<>"			{ return RELOP; }

"+"				{ return ADDOP; }
"-"				{ return ADDOP; }
"or"			{ return ADDOP; }

"*"				{ return MULOP; }
"/"				{ return MULOP; }
"div"			{ return MULOP; }
"mod"			{ return MULOP; }
"and"			{ return MULOP; }

"not"			{ return NOT; }

":="			{ return ASSOP; }
".."			{ return DOTOP; }

{number}		{ return INUM; }
{floating}		{ return RNUM; }
{name}			{ return NAME; }
{whitespace}	{ ; }

\n				{ line_count++; }
.				{ return ERR; }

%%

void yyerror( const char* msg )
{
	fprintf( stderr, "[ERROR] %s", msg );
	exit( 1 );
}
