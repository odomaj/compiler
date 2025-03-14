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
	while (list != NULL)
	{
		list_t *next = list->next;
		(void)free(list->name);
		(void)free(list);
		list = next;
	}
}

inline list_t *insert_list(list_t *list, const char *name)
{
	list_t *new_entry = new_list(name);
	new_entry->next = list;
	return new_entry;
}

list_t *search_list(list_t *list, const char *name)
{
	while (list != NULL)
	{
		if (strcmp(name, list->name) == 0)
			return list;
		list = list->next;
	}
	return NULL;
}
