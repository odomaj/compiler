#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "utils.h"

tree_t *make_num(double value)
{
    tree_t *tree = malloc(sizeof(tree_t));
    assert(tree != NULL);
    tree->token.type = NUM;
    tree->token.data = malloc(sizeof(double));
    assert(tree->token.data != NULL);
    memcpy(tree->token.data, &value, sizeof(double));
    tree->left = NULL;
    tree->right = NULL;
    return tree;
}

tree_t *make_op(char operator, tree_t * left_value, tree_t *right_value)
{
    tree_t *tree = malloc(sizeof(tree_t));
    assert(tree != NULL);
    tree->token.type = OPERATOR;
    tree->token.data = malloc(sizeof(char));
    assert(tree->token.data != NULL);
    memcpy(tree->token.data, &operator, sizeof(char));
    tree->left = left_value;
    tree->right = right_value;
    return tree;
}

tree_t *make_tree(token_t token, tree_t *left, tree_t *right)
{
    tree_t *tree = malloc(sizeof(tree_t));
    assert(tree != NULL);
    tree->token = token;
    tree->left = left;
    tree->right = right;
    return tree;
}

void free_tree(tree_t *tree)
{
    if (tree == NULL)
        return;
    (void)free(tree->token.data);
    (void)free_tree(tree->left);
    (void)free_tree(tree->right);
    (void)free(tree);
}

inline void free_token(token_t token)
{
    free(token.data);
}

double get_num(token_t token)
{
    assert(token.type == NUM);
    return *(double *)token.data;
}

char get_op(token_t token)
{
    assert(token.type == OPERATOR);
    return *(char *)token.data;
}

void print_tree_h(tree_t *tree, uint8_t depth)
{
    if (tree == NULL)
        return;
    for (uint8_t i = 0; i < depth * 4; i++)
    {
        printf(" ");
    }
    switch (tree->token.type)
    {
    case OPERATOR:
        printf("[OP:  %c]\n", get_op(tree->token));
        print_tree_h(tree->left, depth + 1);
        print_tree_h(tree->right, depth + 1);
        break;
    case NUM:
        printf("[NUM: %lf]\n", get_num(tree->token));
        print_tree_h(tree->left, depth + 1);
        print_tree_h(tree->right, depth + 1);
        break;
    default:
        printf("[ERROR: %u]\n", tree->token.type);
    }
}

inline void print_tree(tree_t *tree)
{
    print_tree_h(tree, 0);
}
