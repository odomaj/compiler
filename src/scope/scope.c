#include <stdlib.h>
#include <assert.h>

#include "scope.h"

scope_t *make_scope(scope_t *prev)
{
	scope_t *scope = malloc(sizeof(*scope));
	assert(scope != NULL);
	scope->next = NULL;
	scope->prev = prev;
	for (int i = 0; i < TABLE_SIZE; i++)
		(void)allocate_list(&(scope->table[i]));
	return scope;
}

void free_scope(scope_t *scope)
{
	scope_t *next;
	while (scope != NULL)
	{
		next = scope->next;
		for (int i = 0; i < TABLE_SIZE; i++)
			(void)free_list(&(scope->table[i]));
		(void)free(scope);
		scope = next;
	}
}

stack_t *make_stack(void)
{
	stack_t *stack = malloc(sizeof(*stack));
	assert(stack != NULL);
	stack->base.next = NULL;
	stack->base.prev = NULL;
	for (int i = 0; i < TABLE_SIZE; i++)
		(void)allocate_list(&(stack->base.table[i]));
	return stack;
}

void free_stack(stack_t *stack)
{
	if (stack == NULL)
		return;
	(void)free_scope(stack->base.next);
	(void)free(stack);
}
