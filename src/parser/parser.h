#ifndef COMPILER_PARSER_PARSER_H
#define COMPILER_PARSER_PARSER_H

#include <stdio.h>

#include "scope.h"
#include "tree.h"

int yylex(void);
void yyerror(const char *);

int parse(const char *);

#endif
