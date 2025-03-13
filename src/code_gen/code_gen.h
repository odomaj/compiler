#ifndef COMPILER_CODE_GEN_CODE_GEN
#define COMPILER_CODE_GEN_CODE_GEN

#include <stdint.h>

#include "tree.h"

#define RIGHT_NODE 0
#define LEFT_NODE 1

typedef struct reg_s
{
    char *mem;
    struct reg_s *next;
} reg_t;

typedef struct
{
    reg_t *top;
    uint32_t len;
} register_stack_t;

int code_gen(syntax_tree_t *tree, register_stack_t *stack);

void label_tree(syntax_tree_t *tree);
uint8_t label_tree_h(syntax_tree_t *tree, uint8_t type);
int gencode(syntax_tree_t *tree, register_stack_t *r_stack, register_stack_t *t_stack);

void push(register_stack_t *stack, reg_t *mem);
reg_t *pop(register_stack_t *stack);

void swap(register_stack_t *stack);

reg_t *new_register(char *mem);
void free_register(reg_t *mem);

void clear(register_stack_t *stack);

#endif
