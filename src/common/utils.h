#ifndef COMPILER_COMMON_UTILS_H
#define COMPILER_COMMON_UTILS_H

#include "defs.h"

typedef struct
{
    uint8_t type;
    void *data;
} token_t;

typedef struct tree_s
{
    token_t token;
    struct tree_s *left;
    struct tree_s *right;
} tree_t;

tree_t *make_num(double value);
tree_t *make_op(char operator, tree_t * left_value, tree_t *right_value);

tree_t *make_tree(token_t token, tree_t *left, tree_t *right);

void free_tree(tree_t *tree);
void free_token(token_t token);

double get_num(token_t token);
char get_op(token_t token);

void print_tree(tree_t *tree);

#endif
