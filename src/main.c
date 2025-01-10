#include <stdio.h>
#include "scanner.h"
#include "parser.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        return 1;
    }
    token_list_t *tree = new_token_list();
    if (scan_file(argv[1], tree))
    {
        return 1;
    }
    printf("result: %i", parse_tree(tree));
}
