#include <stdio.h>

#include "parser.h"
#include "scope.h"
#include "tree.h"

int main(int argc, char **argv)
{
    syntax_tree_t *syntax_tree;
    scope_t *symbol_table;
    fprintf(stderr, "%s\n ", argv[1]);
    parse(argv[1], &syntax_tree, &symbol_table);
    return 0;
}
