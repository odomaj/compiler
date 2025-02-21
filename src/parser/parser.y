%{

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "parser.h"

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

int parse(void)
{
    scope_t scope;
    return yyparse();
}
