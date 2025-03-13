#include <stdlib.h>
#include <assert.h>

#include "scope.h"

scope_t *make_scope(void)
{
	scope_t *scope = malloc(sizeof(*scope));
	assert(scope != NULL);
	scope->prev = NULL;
	for (int i = 0; i < TABLE_SIZE; i++)
		scope->table[i] = NULL;
	return scope;
}

scope_t *free_scope(scope_t *scope)
{
	if (scope == NULL)
		return NULL;
	for (int i = 0; i < TABLE_SIZE; i++)
		(void)free_list(scope->table[i]);
	scope_t *prev = scope->prev;
	(void)free(scope);
	return prev;
}

inline scope_t *push_scope(scope_t *scope)
{
	scope_t *new_scope = make_scope();
	new_scope->prev = scope;
	return new_scope;
}

inline scope_t *pop_scope(scope_t *scope)
{
	scope_t *prev = scope->prev;
	free_scope(scope);
	return prev;
}

// https://en.m.wikipedia.org/wiki/PJW_hash_function
size_t hash(const char *str)
{
	uint32_t h = 0, high;
	while (*str)
	{
		h = (h << 4) + *str++;
		if (high = h & 0xF0000000)
			h ^= high >> 24;
		h &= ~high;
	}
	assert(h < TABLE_SIZE);
	return (size_t)h;
}

void insert_scope(scope_t *scope, const char *name)
{
	size_t i = hash(name);
	if (scope->table[i] == NULL)
		scope->table[i] = new_list(name);
}

list_t *search_scope(scope_t *scope, const char *name)
{
	size_t i = hash(name);
	while (scope != NULL)
	{
		list_t *hit = search_list(scope->table[i], name);
		if (hit != NULL)
			return hit;
		scope = scope->prev;
	}
	return NULL;
}

list_t *search_scope_depth(scope_t *scope, const char *name, size_t depth)
{
	size_t i = hash(name);
	while (scope != NULL && depth--)
	{
		list_t *hit = search_list(scope->table[i], name);
		if (hit != NULL)
			return hit;
		scope = scope->prev;
	}
	return NULL;
}
