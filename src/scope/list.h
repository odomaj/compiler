#ifndef COMPILER_COMMON_SCOPE_LIST_H
#define COMPILER_COMMON_SCOPE_LIST_H

#include <stdint.h>

#include "type.h"

#define CLASS_NAME 0
#define CLASS_FUNCTION 1
#define CLASS_PROCEDURE 2

typedef struct list_s
{
	char *name;
	// NAME FUNCTION PARAMETER
	uint8_t class;

	uint8_t function_has_return;

	type_t type;

	struct list_s *function_args;

	struct list_s *next;
} list_t;

// funcs for scoping

list_t *new_list(const char *nam, uint8_t class);
void free_list(list_t *list);

list_t *insert_list(list_t *list, const char *name, uint8_t class);

list_t *search_list(list_t *list, const char *name);

// funcs for parameters

list_t *append_list(list_t *front, list_t *back);

#endif
