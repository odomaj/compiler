#ifndef COMPILER_COMMON_SCOPE_SCOPE_H
#define COMPILER_COMMON_SCOPE_SCOPE_H

#include "list.h"

#define TABLE_SIZE 211

typedef list_t table_t[TABLE_SIZE];

typedef struct scope_s
{
	table_t table;
	struct scope_s *prev;
} scope_t;

scope_t *make_scope(void);
scope_t *free_scope(scope_t *scope);

scope_t *push_scope(scope_t *scope);
scope_t *pop_scope(scope_t *scope);

size_t hash(const char *str);

uint8_t insert_scope(scope_t *scope, const char *name);
list_t *search_scope(scope_t *scope, const char *name);

#endif
