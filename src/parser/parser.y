%{

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int yylex(void);
void yyerror(const char *);

%}

%union
{
    int ival;
}

%token <ival> NUM

%%

expr: expr '+' expr
    | expr '*' expr
    | '(' expr ')'
    | NUM
    ;

%%

int main()
{
    return yyparse();
}
