#ifndef COMPILER_PARSER_PARSER_H
#define COMPILER_PARSER_PARSER_H

#include <stdio.h>

#include "scope.h"
#include "tree.h"
#include "utils.h"

int yylex(void);
void yyerror(syntax_tree_t **, scope_t *, const char *);

int parse(const char *, syntax_tree_t **, scope_t **);

#endif
