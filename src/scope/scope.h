#ifndef COMPILER_COMMON_SCOPE_SCOPE_H
#define COMPILER_COMMON_SCOPE_SCOPE_H

#include "list.h"

#define TABLE_SIZE 211

typedef list_t *table_t[TABLE_SIZE];

typedef struct scope_s
{
	table_t table;
	struct scope_s *upper_scope;
	struct scope_s **lower_scopes;
} scope_t;

scope_t *make_scope(scope_t *upper_scope);
scope_t *free_scope(scope_t *scope);

size_t count_scopes(scope_t **lower_scopes);

scope_t *push_scope(scope_t *scope);
scope_t *pop_scope(scope_t *scope);

size_t hash(const char *str);

void insert_scope(scope_t *scope, const char *name);
list_t *search_scope(scope_t *scope, const char *name);
list_t *search_scope_depth(scope_t *scope, const char *name, size_t depth);

#endif
