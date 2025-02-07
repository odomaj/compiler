#include "parser.h"
#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

token_t current_token;

tree_t *parse_file(const char *filepath)
{
    if (!open_scanner(filepath))
        return NULL;
    tree_t *result = NULL;
    if (next_token(&current_token))
        result = sum();
    (void)close_scanner();
    return result;
}

// TODO: remove asserts and improve error handling

tree_t *sum(void)
{
    tree_t *value = product();
    while (current_token.type == OPERATOR)
    {
        switch (get_op(current_token))
        {
        case '+':
        case '-':
            token_t op = current_token;
            assert(next_token(&current_token) != 0);
            value = make_tree(op, value, product());
            break;
        default:
            return value;
        }
    }
    return value;
}

tree_t *product(void)
{
    tree_t *value = power();
    while (current_token.type == OPERATOR)
    {
        switch (get_op(current_token))
        {
        case '*':
        case '/':
            token_t op = current_token;
            assert(next_token(&current_token) != 0);
            value = make_tree(op, value, power());
            break;
        default:
            return value;
        }
    }
    return value;
}

tree_t *power(void)
{
    tree_t *value = bracket();
    if (current_token.type == OPERATOR)
    {
        if (get_op(current_token) == '^')
        {
            token_t op = current_token;
            assert(next_token(&current_token) != 0);
            value = make_tree(op, value, power());
        }
    }
    return value;
}

tree_t *bracket(void)
{
    if (current_token.type == OPERATOR)
    {
        assert(get_op(current_token) == '(');
        free_token(current_token);
        assert(next_token(&current_token) != 0);
        tree_t *result = sum();
        assert(get_op(current_token) == ')');
        free_token(current_token);

        next_token(&current_token);
        return result;
    }
    tree_t *result = make_tree(current_token, NULL, NULL);
    next_token(&current_token);
    return result;
}
