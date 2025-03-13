#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "code_gen.h"

int code_gen(syntax_tree_t *tree, register_stack_t *stack)
{
    (void)label_tree(tree);
    register_stack_t *t_stack = NULL;
    if (stack->len < tree->label)
        // TODO: allocate r_stack
        ;
    return gencode(tree, stack, t_stack);
}

uint8_t label_tree_h(syntax_tree_t *tree, uint8_t type)
{
    if (tree == NULL)
    {
        if (type == LEFT_NODE)
            return LEFT_NODE;
        else
            return RIGHT_NODE;
    }
    uint8_t left = label_tree_h(tree->left, LEFT_NODE);
    uint8_t right = label_tree_h(tree->right, RIGHT_NODE);
    uint8_t label;
    if (left > right)
        label = left;
    else if (right > left)
        label = right;
    else
        label = right + 1;
    return label;
}

inline void label_tree(syntax_tree_t *tree)
{
    label_tree_h(tree, LEFT_NODE);
}

int gencode(syntax_tree_t *tree, register_stack_t *r_stack, register_stack_t *t_stack)
{
}

inline void push(register_stack_t *stack, reg_t *mem)
{
    mem->next = stack->top;
    stack->top = mem;
}

reg_t *pop(register_stack_t *stack)
{
    reg_t *top = stack->top;
    if (top == NULL)
        return NULL;
    stack->top = top->next;
    top->next = NULL;
    return top;
}

void swap(register_stack_t *stack)
{
    reg_t *top = pop(stack);
    reg_t *next = pop(stack);
    if (top == NULL)
        return;
    (void)push(stack, top);
    if (next == NULL)
        return;
    (void)push(stack, next);
}

reg_t *new_register(char *mem)
{
    reg_t *top = malloc(sizeof(*top));
    assert(top != NULL);
    top->mem = strdup(mem);
    top->next = NULL;
    return top;
}

inline void free_register(reg_t *mem)
{
    if (mem == NULL)
        return;
    (void)free(mem->mem);
    (void)free(mem);
}

void clear(register_stack_t *stack)
{
    while (1)
    {
        reg_t *top = pop(stack);
        if (top == NULL)
            return;
        (void)free_register(top);
    }
}
