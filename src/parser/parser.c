#include "parser.h"

#include <stdio.h>

parser_data_t parse_tree(token_list_t *tree)
{
    parser_data_t output = {0};
    // TO DO: perform calculation based on token tree
    tree = get_front(tree);
    token_list_t *next_node = get_next(tree);
    token_t *cur_token = get_token(tree);
    while (cur_token != NULL)
    {
        if (cur_token->data == NULL)
        {
            output.return_code = -1;
            return output;
        }
        switch (cur_token->type)
        {
        case OPERATOR:
            printf("%c", *(char *)(cur_token->data));
            break;
        case INT:
            printf("%i", *(int *)(cur_token->data));
            break;
        }
        remove_token(tree);
        tree = next_node;
        next_node = get_next(next_node);
        cur_token = get_token(tree);
    }
    return output;
}

parser_data_t sum(token_list_t *tree)
{
    parser_data_t output = {0};
    if (tree == NULL)
    {
        output.return_code = -1;
        return output;
    }
    int *value = (int *)(get_token(tree)->data);
    parser_data_t next_output = sum_help(get_next(tree));
    return output;
}

parser_data_t sum_help(token_list_t *tree)
{
    parser_data_t output = {0};
    token_t *token = get_token(tree);
    if (token->data == NULL)
    {
        return output;
    }
    if (token->type != OPERATOR)
    {
        output.return_code = -1;
        return output;
    }
    char *operator=(char *)(token->data);
    switch (*operator)
    {
    case '+':
        parser_data_t next_output = sum_help(get_next(tree));
    case '-':
    default:
        output.return_code = -1;
        return output;
    }
}

parser_data_t product(token_list_t *tree)
{
}

parser_data_t product_help(token_list_t *tree)
{
    parser_data_t output = {0};
    token_t *token = get_token(tree);
    if (token->data == NULL)
    {
        return output;
    }
    if (token->type != OPERATOR)
    {
        output.return_code = -1;
        return output;
    }
    char *operator=(char *)(token->data);
    switch (*operator)
    {
    case '*':
    case '/':
    default:
        output.return_code = -1;
        return output;
    }
}

parser_data_t power(token_list_t *tree)
{
}

parser_data_t power_help(token_list_t *tree)
{
    parser_data_t output = {0};
    token_t *token = get_token(tree);
    if (token->data == NULL)
    {
        return output;
    }
    if (token->type != OPERATOR)
    {
        output.return_code = -1;
        return output;
    }
    char *operator=(char *)(token->data);
    if (*operator!= '^')
    {
        output.return_code = -1;
        return output;
    }
}

parser_data_t bracket(token_list_t *tree)
{
}
