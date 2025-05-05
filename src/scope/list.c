#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "list.h"

list_t *new_list(const char *name, uint8_t class)
{
	list_t *list = malloc(sizeof(*list));
	assert(list != NULL);

	list->name = strdup(name);
	list->class = class;
	list->type.type_class = TYPE_STANDARD;
	list->type.standard.type = TYPE_EMPTY;
	list->function_has_return = 0;
	list->function_args = NULL;

	list->next = NULL;
	return list;
}

void free_list(list_t *list)
{
	while (list != NULL)
	{
		(void)free_list(list->function_args);
		list_t *next = list->next;
		(void)free(list->name);
		(void)free(list);
		list = next;
	}
}

inline list_t *insert_list(list_t *list, const char *name, uint8_t class)
{
	list_t *new_entry = new_list(name, class);
	new_entry->next = list;
	return new_entry;
}

list_t *search_list(list_t *list, const char *name)
{
	while (list != NULL)
	{
		if (list->name != NULL && strcmp(name, list->name) == 0)
			return list;
		list = list->next;
	}
	return NULL;
}

list_t *append_list(list_t *front, list_t *back)
{
	if (front == NULL)
		return back;
	list_t *first = front;
	while (front->next != NULL)
		front = front->next;
	front->next = back;
	return first;
}