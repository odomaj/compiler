#include <stdio.h>
#include "parser.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("[ERROR] requires 2 arguments, %i given", argc - 1);
    }
    tree_t *tree = parse_file(argv[1]);
    (void)print_tree(tree);
    (void)free_tree(tree);
    return 0;
}
