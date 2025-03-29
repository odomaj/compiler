#include <stdlib.h>
#include <assert.h>

#include "tree.h"

syntax_tree_t *tree_inum(int ival)
{
    syntax_tree_t *tree = malloc(sizeof(*tree));
    assert(tree != NULL);

    tree->type = IVAL;
    tree->value.ival = ival;

    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

syntax_tree_t *tree_rnum(float rval)
{
    syntax_tree_t *tree = malloc(sizeof(*tree));
    assert(tree != NULL);

    tree->type = RVAL;
    tree->value.rval = rval;

    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

syntax_tree_t *tree_op(uint8_t type, uint8_t value, syntax_tree_t *left, syntax_tree_t *right)
{
    syntax_tree_t *tree = malloc(sizeof(*tree));
    assert(tree != NULL);

    tree->type = OPVAL;
    tree->value.op_val.class = type;
    tree->value.op_val.value = value;

    tree->left = left;
    tree->right = right;

    return tree;
}

syntax_tree_t *tree_sym(list_t *sval)
{
    syntax_tree_t *tree = malloc(sizeof(*tree));
    assert(tree != NULL);

    tree->type = SVAL;
    tree->value.sval = sval;

    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

syntax_tree_t *tree_rule(uint8_t rule, uint8_t option, syntax_tree_t *left, syntax_tree_t *right)
{
    syntax_tree_t *tree = malloc(sizeof(*tree));
    assert(tree != NULL);

    tree->type = RULE_VAL;
    tree->value.rule_val.rule = rule;
    tree->value.rule_val.option = option;

    tree->left = left;
    tree->right = right;

    return tree;
}

syntax_tree_t *tree_type(uint8_t type)
{
    syntax_tree_t *tree = malloc(sizeof(*tree));
    assert(tree != NULL);

    tree->type = TVAL;
    tree->value.tval.type = type;

    tree->left = NULL;
    tree->right = NULL;

    return tree;
}

void free_tree(syntax_tree_t *tree)
{
    return;
}
