%{

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"

#define NUM 256
#define ID 257

%}

number		[0-9]+
ident		[a-zA-Z][a-zA-Z0-9]*
whitespace	[ \t]

%%

"+"				{ fprintf( stderr, "[ADDOP:%c]", yytext[0] ); return yytext[0]; }
"*"				{ fprintf( stderr, "[MULLOP:%c]", yytext[0] ); return yytext[0]; }
"("				{ fprintf( stderr, "[%c]", yytext[0] ); return yytext[0]; }
")"				{ fprintf( stderr, "[%c]", yytext[0] ); return yytext[0]; }
{number}		{ fprintf( stderr, "[NUM:%d]", atoi( yytext ) ); return NUM; }
{ident}			{ fprintf( stderr, "[ID:%s]", yytext ); return NUM; }
{whitespace}	{ ; }
\n				{ fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }
.				{ fprintf( stderr, "%c", yytext[0] ); return yytext[0]; }

%%

int yyerror( char* msg )
{
	fprintf( stderr, "[ERROR] %s", msg );
	exit( 1 );
}
