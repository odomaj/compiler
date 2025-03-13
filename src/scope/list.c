#include <stdlib.h>
#include <assert.h>

#include "list.h"

void allocate_list(list_t *dest)
{
}

inline list_t *make_list(void)
{
	list_t *dest = malloc(sizeof(*dest));
	assert(dest != NULL);
	(void)allocate_list(dest);
	return dest;
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
