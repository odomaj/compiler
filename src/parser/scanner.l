%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "parser_.h"

extern FILE *yyin;

%}

%option noyywrap
%x COMMENT

number		[0-9]+
floating	[0-9]*"."[0-9]+
name		[_a-zA-Z][_a-zA-Z0-9]*
whitespace	[ \t\r\n]+

%%

"(*"			{ BEGIN COMMENT; }
<COMMENT>.		|
<COMMENT>\n		{ ; }
<COMMENT>"*)"	{ BEGIN INITIAL; }

"program"		{ fprintf(stderr, "[program]"); return PROGRAM; }
"procedure"		{ fprintf(stderr, "[procedure]"); return PROCEDURE; }
"function"		{ fprintf(stderr, "[function]"); return FUNCTION; }
"var"			{ fprintf(stderr, "[var]"); return VAR; }
"array"			{ fprintf(stderr, "[array]"); return ARRAY; }
"of"			{ fprintf(stderr, "[of]"); return OF; }
"begin"			{ fprintf(stderr, "[begin]"); return BBEGIN; }
"end"			{ fprintf(stderr, "[end]"); return END; }
"integer"		{ fprintf(stderr, "[integer]"); return INTEGER; }
"real"			{ fprintf(stderr, "[real]"); return REAL; }
"if"			{ fprintf(stderr, "[if]"); return IF; }
"then"			{ fprintf(stderr, "[then]"); return THEN; }
"else"			{ fprintf(stderr, "[else]"); return ELSE; }
"while"			{ fprintf(stderr, "[while]"); return WHILE; }
"do"			{ fprintf(stderr, "[do]"); return DO; }
"repeat"		{ fprintf(stderr, "[repeat]"); return REPEAT; }
"until"			{ fprintf(stderr, "[until]"); return UNTIL; }
"for"			{ fprintf(stderr, "[for]"); return FOR; }
"to"			{ fprintf(stderr, "[to]"); return TO; }

"<"				{ fprintf(stderr, "[<]"); yylval.opval = LT; return RELOP; }
"<="			{ fprintf(stderr, "[<=]"); yylval.opval = LE; return RELOP; }
">"				{ fprintf(stderr, "[>]"); yylval.opval = GT; return RELOP; }
">="			{ fprintf(stderr, "[>=]"); yylval.opval = GE; return RELOP; }
"="				{ fprintf(stderr, "[=]"); yylval.opval = EQ; return RELOP; }
"<>"			{ fprintf(stderr, "[<>]"); yylval.opval = NE; return RELOP; }

"+"				{ fprintf(stderr, "[+]"); yylval.opval = PLUS; return ADDOP; }
"-"				{ fprintf(stderr, "[-]"); yylval.opval = MINUS; return ADDOP; }
"or"			{ fprintf(stderr, "[or]"); yylval.opval = OR; return ADDOP; }

"*"				{ fprintf(stderr, "[*]"); yylval.opval = STAR; return MULOP; }
"/"				{ fprintf(stderr, "[/]"); yylval.opval = SLASH; return MULOP; }
"div"			{ fprintf(stderr, "[div]"); yylval.opval = DIV; return MULOP; }
"mod"			{ fprintf(stderr, "[mod]"); yylval.opval = MOD; return MULOP; }
"and"			{ fprintf(stderr, "[and]"); yylval.opval = AND; return MULOP; }

"not"			{ fprintf(stderr, "[not]"); return NOT; }

":="			{ fprintf(stderr, "[:=]"); return ASSOP; }
".."			{ fprintf(stderr, "[..]"); return DOTOP; }

{number}		{ fprintf(stderr, "[number]"); yylval.ival = atoi( yytext ); return INUM; }
{floating}		{ fprintf(stderr, "[float]"); yylval.rval = atof( yytext ); return RNUM; }
{name}			{ fprintf(stderr, "[name]"); yylval.sval = strdup( yytext ); return NAME; }
{whitespace}	{ ; }

"("				{ fprintf(stderr, "("); return OPEN_P; }
")"				{ fprintf(stderr, "[)]"); return CLOSE_P; }
"["				{ fprintf(stderr, "[[]"); return OPEN_B; }
"]"				{ fprintf(stderr, "[]]"); return CLOSE_B; }
";"				{ fprintf(stderr, "[;]"); return SEMICOLON; }
":"				{ fprintf(stderr, "[:]"); return COLON; }
"."				{ fprintf(stderr, "[.]"); return DOT; }

.				{ fprintf(stderr, "[err]"); return ERR; }

%%

void yyerror( const char* msg )
{
	fprintf( stderr, "[ERROR] %s\n", msg );
}
