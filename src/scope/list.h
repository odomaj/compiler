#ifndef COMPILER_COMMON_SCOPE_LIST_H
#define COMPILER_COMMON_SCOPE_LIST_H

#include <stdint.h>

#include "type.h"

typedef struct list_s
{
	char *name;
	// NAME FUNCTION PARAMETER
	type_t type;

	struct list_s *next;
} list_t;

list_t *new_list(const char *name);
void free_list(list_t *list);

list_t *insert_list(list_t *list, const char *name);

list_t *search_list(list_t *list, const char *name);

list_t *append_list_element(list_t *list, list_t *element);
list_t *append_list(list_t *front, list_t *back);

void type_list(list_t *list, type_t type);

#endif
