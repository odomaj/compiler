%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "parser_.h"

/* extern int line_count; */

%}

%option noyywrap
%option nounput
%x COMMENT

number		[0-9]+
floating	[0-9]*"."[0-9]+
name		[_a-zA-Z][_a-zA-Z0-9]*
whitespace	[ \t]+

%%

"(*"			{ BEGIN COMMENT; }
<COMMENT>.		|
<COMMENT>\n		{ ; }
<COMMENT>"*)"	{ BEGIN INITIAL; }

"program"		{ return PROGRAM; }
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
"repeat"		{ return REPEAT; }
"until"			{ return UNTIL; }
"for"			{ return FOR; }
"to"			{ return TO; }

"<"				{ yylval.opval = LT; return RELOP; }
"<="			{ yylval.opval = LE; return RELOP; }
">"				{ yylval.opval = GT; return RELOP; }
">="			{ yylval.opval = GE; return RELOP; }
"="				{ yylval.opval = EQ; return RELOP; }
"<>"			{ yylval.opval = NE; return RELOP; }

"+"				{ yylval.opval = PLUS; return ADDOP; }
"-"				{ yylval.opval = MINUS; return ADDOP; }
"or"			{ yylval.opval = OR; return ADDOP; }

"*"				{ yylval.opval = STAR; return MULOP; }
"/"				{ yylval.opval = SLASH; return MULOP; }
"div"			{ yylval.opval = DIV; return MULOP; }
"mod"			{ yylval.opval = MOD; return MULOP; }
"and"			{ yylval.opval = AND; return MULOP; }

"not"			{ return NOT; }

":="			{ return ASSOP; }
".."			{ return DOTOP; }

{number}		{ yylval.ival = atoi( yytext ); return INUM; }
{floating}		{ yylval.rval = atof( yytext ); return RNUM; }
{name}			{ yylval.sval = strdup( yytext ); return NAME; }
{whitespace}	{ ; }

"("				{ return OPEN_P; }
")"				{ return CLOSE_P; }
"["				{ return OPEN_B; }
"]"				{ return CLOSE_B; }
";"				{ return SEMICOLON; }
":"				{ return COLON; }
"."				{ return DOT; }

\n				{ /* line_count++; */ }
.				{ return ERR; }

%%

void yyerror( FILE *file, const char* msg )
{
	fprintf( stderr, "[ERROR] %s\n", msg );
}
