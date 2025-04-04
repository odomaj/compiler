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

"program"		{ 
				#ifndef NDEBUG
					fprintf(stderr, "[program]");
				#endif
					return PROGRAM; 
				}
"procedure"		{
				#ifndef NDEBUG
					fprintf(stderr, "[procedure]");
				#endif
					return PROCEDURE;
				}
"function"		{
				#ifndef NDEBUG
					fprintf(stderr, "[function]");
				#endif
					return FUNCTION;
				}
"var"			{
				#ifndef NDEBUG
					fprintf(stderr, "[var]");
				#endif
					return VAR;
				}
"array"			{
				#ifndef NDEBUG
					fprintf(stderr, "[array]");
				#endif
					return ARRAY;
				}
"of"			{
				#ifndef NDEBUG
					fprintf(stderr, "[of]");
				#endif
					return OF;
				}
"begin"			{
				#ifndef NDEBUG
					fprintf(stderr, "[begin]");
				#endif
					return BBEGIN;
				}
"end"			{
				#ifndef NDEBUG
					fprintf(stderr, "[end]");
				#endif
					return END;
				}
"integer"		{
				#ifndef NDEBUG
					fprintf(stderr, "[integer]");
				#endif
					return INTEGER;
				}
"real"			{
				#ifndef NDEBUG
					fprintf(stderr, "[real]");
				#endif
					return REAL;
				}
"if"			{
				#ifndef NDEBUG
					fprintf(stderr, "[if]");
				#endif
					return IF;
				}
"then"			{
				#ifndef NDEBUG
					fprintf(stderr, "[then]");
				#endif
					return THEN;
				}
"else"			{
				#ifndef NDEBUG
					fprintf(stderr, "[else]");
				#endif
					return ELSE;
				}
"while"			{
				#ifndef NDEBUG
					fprintf(stderr, "[while]");
				#endif
					return WHILE;
				}
"do"			{
				#ifndef NDEBUG
					fprintf(stderr, "[do]");
				#endif
					return DO;
				}
"repeat"		{
				#ifndef NDEBUG
					fprintf(stderr, "[repeat]");
				#endif
					return REPEAT;
				}
"until"			{
				#ifndef NDEBUG
					fprintf(stderr, "[until]");
				#endif
					return UNTIL;
				}
"for"			{
				#ifndef NDEBUG
					fprintf(stderr, "[for]");
				#endif
					return FOR;
				}
"to"			{
				#ifndef NDEBUG
					fprintf(stderr, "[to]");
				#endif
					return TO;
				}

"<"				{
				#ifndef NDEBUG
					fprintf(stderr, "[<]");
				#endif
					yylval.opval = LT;
					return RELOP;
				}
"<="			{
				#ifndef NDEBUG
					fprintf(stderr, "[<=]");
				#endif
					yylval.opval = LE;
					return RELOP; }
">"				{
				#ifndef NDEBUG
					fprintf(stderr, "[>]");
				#endif
					yylval.opval = GT;
					return RELOP;
				}
">="			{
				#ifndef NDEBUG
					fprintf(stderr, "[>=]");
				#endif
					yylval.opval = GE;
					return RELOP;
				}
"="				{
				#ifndef NDEBUG
					fprintf(stderr, "[=]");
				#endif
					yylval.opval = EQ;
					return RELOP;
				}
"<>"			{
				#ifndef NDEBUG
					fprintf(stderr, "[<>]");
				#endif
					yylval.opval = NE;
					return RELOP;
				}

"+"				{
				#ifndef NDEBUG
					fprintf(stderr, "[+]");
				#endif
					yylval.opval = PLUS;
					return ADDOP;
				}
"-"				{
				#ifndef NDEBUG
					fprintf(stderr, "[-]");
				#endif
					yylval.opval = MINUS;
					return ADDOP;
				}
"or"			{
				#ifndef NDEBUG
					fprintf(stderr, "[or]");
				#endif
					yylval.opval = OR;
					return ADDOP;
				}

"*"				{
				#ifndef NDEBUG
					fprintf(stderr, "[*]");
				#endif
					yylval.opval = STAR;
					return MULOP;
				}
"/"				{
				#ifndef NDEBUG
					fprintf(stderr, "[/]");
				#endif
					yylval.opval = SLASH;
					return MULOP;
				}
"div"			{
				#ifndef NDEBUG
					fprintf(stderr, "[div]");
				#endif
					yylval.opval = DIV;
					return MULOP;
				}
"mod"			{
				#ifndef NDEBUG
					fprintf(stderr, "[mod]");
				#endif
					yylval.opval = MOD;
					return MULOP;
				}
"and"			{
				#ifndef NDEBUG
					fprintf(stderr, "[and]");
				#endif
					yylval.opval = AND;
					return MULOP;
				}

"not"			{
				#ifndef NDEBUG
					fprintf(stderr, "[not]");
				#endif
					return NOT;
				}

":="			{
				#ifndef NDEBUG
					fprintf(stderr, "[:=]");
				#endif
					return ASSOP;
				}
".."			{
				#ifndef NDEBUG
					fprintf(stderr, "[..]");
				#endif
					return DOTOP;
				}

{number}		{
				#ifndef NDEBUG
					fprintf(stderr, "[number]");
				#endif
					yylval.ival = atoi( yytext );
					return INUM;
				}
{floating}		{
				#ifndef NDEBUG
					fprintf(stderr, "[float]");
				#endif
					yylval.rval = atof( yytext );
					return RNUM;
				}
{name}			{
				#ifndef NDEBUG
					fprintf(stderr, "[name]");
				#endif
					yylval.sval = strdup( yytext );
					return NAME;
				}
{whitespace}	{ ; }

","				{
				#ifndef NDEBUG
					fprintf(stderr, "[,]");
				#endif
					return COMMA;
				}
"("				{
				#ifndef NDEBUG
					fprintf(stderr, "[(]");
				#endif
					return OPEN_P;
				}
")"				{
				#ifndef NDEBUG
					fprintf(stderr, "[)]");
				#endif
					return CLOSE_P;
				}
"["				{
				#ifndef NDEBUG
					fprintf(stderr, "[[]");
				#endif
					return OPEN_B;
				}
"]"				{
				#ifndef NDEBUG
					fprintf(stderr, "[]]");
				#endif
					return CLOSE_B;
				}
";"				{
				#ifndef NDEBUG
					fprintf(stderr, "[;]");
				#endif
					return SEMICOLON;
				}
":"				{
				#ifndef NDEBUG
					fprintf(stderr, "[:]");
				#endif
					return COLON;
				}
"."				{
				#ifndef NDEBUG
					fprintf(stderr, "[.]\n");
				#endif
					return DOT;
				}

.				{
				#ifndef NDEBUG
					fprintf(stderr, "[err]");
				#endif
					return ERR;
				}

%%

void yyerror( syntax_tree_t **syntax_tree, scope_t *symbol_table, const char *msg )
{
	fprintf( stderr, "[ERROR] %s\n", msg );
	YY_FLUSH_BUFFER;
}
