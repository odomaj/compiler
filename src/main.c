#include <stdio.h>

#include "parser.h"
#include "scope.h"

int main(int argc, char **argv)
{
    stack_t *stack = make_stack();
    free_stack(stack);
    return 0;
}
