#include <stdlib.h>
#include <assert.h>

#include <stdio.h>

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

/**
 * get the type object from a TYPE rule for parser
 */
type_t tree_to_type(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    assert(tree->value.rule_val.rule == TREE_STANDARD_TYPE || tree->value.rule_val.rule == TREE_TYPE);
    switch (tree->value.rule_val.rule)
    {
    case TREE_STANDARD_TYPE:
        return tree_to_stype(tree->right);
    case TREE_TYPE:
        type_t type = tree_to_type(tree->right);
        if (tree->value.rule_val.option == RULE_1)
            return type;
        type.type_class = TYPE_ARRAY;
        type.array = tree_to_atype(tree->left);
        return type;
    }
    // should never happen
    type_t type;
    type.type_class = TYPE_STANDARD;
    type.standard.type = TYPE_EMPTY;
    return type;
}

type_t tree_to_stype(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == TVAL);
    type_t type;
    type.type_class = TYPE_STANDARD;
    type.standard = tree->value.tval;
    return type;
}

type_array_t tree_to_atype(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    assert(tree->value.rule_val.rule == TREE_RANGE);
    assert(tree->value.rule_val.option == RULE_1);
    assert(tree->left != NULL);
    assert(tree->right != NULL);
    assert(tree->left->type == IVAL);
    assert(tree->right->type == IVAL);
    type_array_t type;
    type.start_i = tree->left->value.ival;
    type.end_i = tree->right->value.ival;
    return type;
}

void declare_types(syntax_tree_t *id_list, syntax_tree_t *type)
{
    type_t ttype = tree_to_type(type);
    assert(id_list != NULL);
    assert(id_list->type == RULE_VAL);
    assert(id_list->value.rule_val.rule == TREE_IDENTIFIER_LIST);
    while (id_list->value.rule_val.option == RULE_2)
    {
        (void)declare_type(id_list->right, ttype);
        id_list = id_list->left;
        assert(id_list != NULL);
        assert(id_list->type == RULE_VAL);
        assert(id_list->value.rule_val.rule == TREE_IDENTIFIER_LIST);
    }
    assert(id_list->value.rule_val.option == RULE_1);
    (void)declare_type(id_list->right, ttype);
}

inline void declare_type(syntax_tree_t *id, type_t type)
{
    assert(id != NULL);
    assert(id->type == SVAL);
    id->value.sval->type = type;
}

/**
 * outputs if the types of the left tree and right tree are not the same
 * does not perform a check of the subtrees
 */
inline uint8_t mismatched_types(syntax_tree_t *left, syntax_tree_t *right)
{
    return type_check(get_saved_type(left), get_saved_type(right));
}

inline uint8_t is_standard_type(syntax_tree_t *tree)
{
    type_t type = get_saved_type(tree);
    assert(type.standard.type != TYPE_EMPTY);
    return type.type_class == TYPE_STANDARD;
}

uint8_t check_int(syntax_tree_t *tree)
{
    type_t type;
    type.type_class = TYPE_STANDARD;
    type.standard.type = TYPE_INT;
    return type_check(get_saved_type(tree), type);
}

uint8_t type_check(type_t a, type_t b)
{
    if (a.type_class != b.type_class)
        return 1;
    if (a.standard.type != b.standard.type)
        return 1;
    return 0;
}

/**
 * get the type object from an expression rule for parser
 */
type_t get_saved_type(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    switch (tree->value.rule_val.rule)
    {
    case TREE_EXPRESSION:
        return expression_type(tree);
    case TREE_SIMPLE_EXPRESSION:
        return simple_expression_type(tree);
    case TREE_TERM:
        return term_type(tree);
    case TREE_FACTOR:
        return factor_type(tree);
    }
    // this should never happen
    assert(1);
}

type_t expression_type(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    assert(tree->value.rule_val.rule == TREE_EXPRESSION);
    switch (tree->value.rule_val.option)
    {
    case RULE_1:
    case RULE_2:
        return simple_expression_type(tree->right);
    }
    // this should never happen
    assert(1);
}

type_t simple_expression_type(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    assert(tree->value.rule_val.rule == TREE_SIMPLE_EXPRESSION);
    switch (tree->value.rule_val.option)
    {
    case RULE_1:
        return term_type(tree->right);
    case RULE_2:
    case RULE_3:
        assert(tree->right != NULL);
        assert(tree->right->type == OPVAL);
        assert(tree->right->value.op_val.class == TREE_ADDOP);
        return term_type(tree->right->right);
    }
    // this should never happen
    assert(1);
}

type_t term_type(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    assert(tree->value.rule_val.rule == TREE_TERM);
    switch (tree->value.rule_val.option)
    {
    case RULE_1:
    case RULE_2:
        return factor_type(tree->right);
    }
    // this should never happen
    assert(1);
}

type_t factor_type(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    assert(tree->value.rule_val.rule == TREE_FACTOR);
    type_t type;
    switch (tree->value.rule_val.option)
    {
    case RULE_1:
        assert(tree->right != NULL);
        assert(tree->right->type == SVAL);
        assert(tree->right->value.sval != NULL);
        return tree->right->value.sval->type;
    case RULE_2:
    case RULE_3:
        assert(tree->left != NULL);
        assert(tree->left->type == SVAL);
        assert(tree->left->value.sval != NULL);
        return tree->left->value.sval->type;
    case RULE_4:
        type.type_class = TYPE_STANDARD;
        type.standard.type = TYPE_INT;
        return type;
    case RULE_5:
        type.type_class = TYPE_STANDARD;
        type.standard.type = TYPE_INT;
        return type;
    case RULE_6:
        return expression_type(tree->right);
    case RULE_7:
        return factor_type(tree->right);
    }
    // this should never happen
    assert(1);
}

inline uint8_t symbol_is_int(list_t *symbol)
{
    return symbol->type.type_class == TYPE_STANDARD && symbol->type.standard.type == TYPE_INT;
}

uint8_t check_subprogram(syntax_tree_t *tree, scope_t *scope)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    assert(tree->value.rule_val.rule == TREE_SUBPROGRAM_HEADER);
    assert(tree->left != NULL);
    assert(tree->left->type == SVAL);
    list_t *subprogram = tree->left->value.sval;
    switch (tree->value.rule_val.option)
    {
    case RULE_1:
        assert(subprogram->class == CLASS_FUNCTION);
        return subprogram->function_has_return != 1;
    case RULE_2:
        assert(subprogram->class == CLASS_PROCEDURE);
        return subprogram->function_has_return != 0;
    }
    assert(1);
}

list_t *interpret_var(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == RULE_VAL);
    assert(tree->value.rule_val.rule == TREE_VARIABLE);
    switch (tree->value.rule_val.option)
    {
    case RULE_1:
        return get_sym(tree->right);
    case RULE_2:
        return get_sym(tree->left);
    }
    assert(1);
}

inline list_t *get_sym(syntax_tree_t *tree)
{
    assert(tree != NULL);
    assert(tree->type == SVAL);
    return tree->value.sval;
}

inline void type_func(list_t *list, syntax_tree_t *tree)
{
    assert(list->class == CLASS_FUNCTION);
    list->type = tree_to_type(tree);
}

uint8_t statement_mismatched_types(list_t *list, syntax_tree_t *tree)
{
    assert(list != NULL);
    if (list->class == CLASS_PROCEDURE || list->class == CLASS_FUNCTION)
        list->function_has_return = 1;
    // return no error here to provide more clear error message in later catch
    if (list->class == CLASS_PROCEDURE)
        return 0;
    return type_check(list->type, expression_type(tree));
}
