#ifndef COMPILER_COMMON_SCOPE_LIST_H
#define COMPILER_COMMON_SCOPE_LIST_H

#include <stdint.h>

typedef struct list_s
{
	char *name;
	// NAME FUNCTION PARAMETER
	uint8_t class;

	uint8_t type;

	struct list_s *next;
} list_t;

list_t *new_list(const char *name);
void free_list(list_t *list);

uint8_t insert_list(list_t *scope, const char *name);

list_t *search_list(list_t *scope, const char *name);

#endif
