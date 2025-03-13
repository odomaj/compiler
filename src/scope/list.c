#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list.h"

list_t *new_list(const char *name)
{
	list_t *list = malloc(sizeof(*list));
	assert(list != NULL);

	list->name = strdup(name);
	list->class = 0;
	list->type = 0;

	list->next = NULL;
	return list;
}

void free_list(list_t *list)
{
}

uint8_t insert_list(list_t *scope, const char *name)
{
}

list_t *search_list(list_t *scope, const char *name)
{
}
