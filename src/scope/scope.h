#ifndef COMPILER_COMMON_SCOPE_SCOPE_H
#define COMPILER_COMMON_SCOPE_SCOPE_H

#include "list.h"

#define TABLE_SIZE 211

typedef list_t table_t[TABLE_SIZE];

typedef struct scope_s
{
	table_t table;
	struct scope_s *next;
	struct scope_s *prev;
} scope_t;

typedef struct
{
	scope_t base;
} stack_t;

scope_t *make_scope(scope_t *prev);
void free_scope(scope_t *);

stack_t *make_stack(void);
void free_stack(stack_t *);

#endif
