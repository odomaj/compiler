#ifndef COMPILER_COMMON_UTILS_H
#define COMPILER_COMMON_UTILS_H

#include "defs.h"

typedef struct stack_s
{
    size_t num;
    struct stack_s *next;
} stack_t;

stack_t *new_stack(size_t num);
stack_t *push_num(stack_t *stack, size_t num);
stack_t *pop_num(stack_t *stack);

#endif
