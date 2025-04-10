#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "scope.h"

scope_t *make_scope(scope_t *upper_scope)
{
	scope_t *scope = malloc(sizeof(*scope));
	assert(scope != NULL);
	scope->upper_scope = upper_scope;
	scope->lower_scopes = malloc(sizeof(*(scope->lower_scopes)));
	assert(scope->lower_scopes != NULL);
	scope->lower_scopes[0] = NULL;
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
	for (size_t i = 0; scope->lower_scopes[i] != NULL; i++)
	{
		scope_t *upper_scope = free_scope(scope->lower_scopes[i]);
		assert(upper_scope == scope);
	}
	scope_t *prev = scope->upper_scope;
	(void)free(scope);
	return prev;
}

size_t count_scopes(scope_t **lower_scopes)
{
	size_t count = 0;
	while (lower_scopes[count++] != NULL)
		;
	return count;
}

inline scope_t *push_scope(scope_t *scope)
{
	size_t len = count_scopes(scope->lower_scopes);
	// ensure no overflows
	if (len + 2 < len)
		return NULL;
	scope->lower_scopes = realloc(scope->lower_scopes, (len + 1) * sizeof(*(scope->lower_scopes)));
	assert(scope->lower_scopes != NULL);
	scope->lower_scopes[len] = make_scope(scope);
	return scope->lower_scopes[len];
}

inline scope_t *pop_scope(scope_t *scope)
{
	return scope->upper_scope;
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
	return (size_t)(h % TABLE_SIZE);
}

inline list_t *insert_scope(scope_t *scope, const char *name)
{
	uint32_t i = hash(name);
	scope->table[i] = insert_list(scope->table[i], name);
	return scope->table[i];
}

list_t *search_scope(scope_t *scope, const char *name)
{
	size_t i = hash(name);
	while (scope != NULL)
	{
		list_t *hit = search_list(scope->table[i], name);
		if (hit != NULL)
			return hit;
		scope = scope->upper_scope;
	}
	return NULL;
}

list_t *search_scope_depth(scope_t *scope, const char *name, size_t depth)
{
	size_t i = hash(name);
	depth++;
	while (scope != NULL && depth--)
	{
		list_t *hit = search_list(scope->table[i], name);
		if (hit != NULL)
			return hit;
		scope = scope->upper_scope;
	}
	return NULL;
}
