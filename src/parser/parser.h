#ifndef COMPILER_PARSER_PARSER_H
#define COMPILER_PARSER_PARSER_H

#include "scope.h"
#include "tree.h"

// TODO: define types
typedef int ptype_t;
typedef int ltype_t;
typedef int lname_t;

int yylex(void);
void yyerror(const char *);

int parse(void);

#endif
