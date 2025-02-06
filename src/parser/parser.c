#include "parser.h"
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>

tree_t *parse_file(const char *filepath)
{
    if (!open_scanner(filepath))
        return NULL;
    token_t token;
    while (next_token(&token))
    {
        if (token.type == OPERATOR)
            printf("%c\n", *(char *)token.data);
        else if (token.type == NUM)
            printf("%lf\n", *(double *)token.data);
        else
            printf("YOURE STUPID YOU DUMB BITCH\n");
        free(token.data);
        token.data = NULL;
    }
    if (token.type == OPERATOR)
        printf("%c\n", *(char *)token.data);
    else if (token.type == NUM)
        printf("%lf\n", *(double *)token.data);
    else
        printf("YOURE STUPID YOU DUMB BITCH\n");
    (void)close_scanner();
    return make_tree(token, NULL, NULL);
}

tree_t *sum()
{
}

tree_t *sum_help()
{
}

tree_t *product()
{
}

tree_t *product_help()
{
}

tree_t *power()
{
}

tree_t *power_help()
{
}

tree_t *bracket()
{
}

tree_t *bracket_help()
{
}
