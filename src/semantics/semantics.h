#ifndef COMPILER_SEMANTICS_SEMANTICS_H
#define COMPILER_SEMANTICS_SEMANTICS_H

#include "tree.h"
#include "scope.h"

typedef struct
{
    syntax_tree_t *tree;
    scope_t *symbols;
} parsed_t;

uint8_t combine_subprograms(parsed_t *dest, parsed_t *src);

#endif
