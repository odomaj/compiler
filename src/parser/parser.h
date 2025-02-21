#ifndef COMPILER_PARSER_PARSER_H
#define COMPILER_PARSER_PARSER_H

#include "scope.h"

int yylex(void);
void yyerror(const char *);

int parse(void);

#endif
