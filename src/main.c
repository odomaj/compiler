#include <stdio.h>

#include "parser.h"
#include "scope.h"
#include "tree.h"

int main(int argc, char **argv)
{
    syntax_tree_t *tree;
    fprintf(stderr, "%s\n ", argv[1]);
    parse(argv[1], &tree);
    return 0;
}
