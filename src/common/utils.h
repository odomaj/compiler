#ifndef COMPILER_COMMON_UTILS_H
#define COMPILER_COMMON_UTILS_H

#include "defs.h"

typedef struct
{
    uint8_t type;
    void *data;
} token_t;

typedef struct
{
    token_t *token;
    void *next;
    void *prev;
} token_list_t;

token_list_t *new_token_list();
token_t *new_token(uint8_t type, void *data);

token_t *get_token(token_list_t *token_list);

token_list_t *get_head(token_list_t *token_list);
token_list_t *get_front(token_list_t *token_list);
token_list_t *get_back(token_list_t *token_list);
token_list_t *get_next(token_list_t *token_list);
token_list_t *get_prev(token_list_t *token_list);

token_list_t *push_prev(token_t *token, token_list_t *token_list);
token_list_t *push_next(token_t *token, token_list_t *token_list);

uint8_t remove_token(token_list_t *token_list);

token_list_t *push_back(token_t *token, token_list_t *token_list);
token_list_t *push_front(token_t *token, token_list_t *token_list);

void delete_token(token_t *token);

#endif
