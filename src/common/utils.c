#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

stack_t *new_stack(size_t num)
{
    stack_t *stack = malloc(sizeof(*stack));
    assert(stack != NULL);

    stack->next = NULL;
    stack->num = num;
    return stack;
}

inline stack_t *push_num(stack_t *stack, size_t num)
{
    stack_t *top = new_stack(num);
    top->next = stack;
    return top;
}

stack_t *pop_num(stack_t *stack)
{
    stack_t *next = stack->next;
    (void)free(stack);
    return next;
}
