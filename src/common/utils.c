#include <stdlib.h>
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
