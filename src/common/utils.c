#include "utils.h"
#include "string.h"
#include "stdlib.h"

token_list_t *new_token_list()
{
    token_list_t *token_list = (token_list_t *)malloc(sizeof(token_list_t));
    token_list->next = token_list;
    token_list->prev = token_list;
    token_list->token = NULL;
    return token_list;
}

token_t *new_token(uint8_t type, void *data)
{
    token_t *token = (token_t *)malloc(sizeof(token_t));
    token->type = type;
    switch (type)
    {
    case OPERATOR:
        token->data = (char *)malloc(sizeof(char));
        memcpy(token->data, data, sizeof(char));
        return token;
    case INT:
        token->data = (int *)malloc(sizeof(int));
        memcpy(token->data, data, sizeof(int));
        return token;
    }
    return NULL;
}

inline token_t *get_token(token_list_t *token_list)
{
    if (token_list == NULL)
        return NULL;
    return token_list->token;
}

token_list_t *get_head(token_list_t *token_list)
{
    token_list_t *start_node = token_list;
    while (token_list->token != NULL)
    {
        token_list = (token_list_t *)(token_list->next);
        if (token_list == start_node)
            return start_node;
    }
    return token_list;
}

inline token_list_t *get_front(token_list_t *token_list)
{
    return (token_list_t *)(get_head(token_list)->next);
}

inline token_list_t *get_back(token_list_t *token_list)
{
    return (token_list_t *)(get_head(token_list)->prev);
}

inline token_list_t *get_next(token_list_t *token_list)
{
    return (token_list_t *)(token_list->next);
}

inline token_list_t *get_prev(token_list_t *token_list)
{
    return (token_list_t *)(token_list->prev);
}

token_list_t *push_prev(token_t *token, token_list_t *token_list)
{
    token_list_t *new_node = (token_list_t *)malloc(sizeof(token_list_t));
    new_node->token = token;
    token_list_t *prev_back = token_list->prev;
    prev_back->next = new_node;
    new_node->prev = prev_back;
    new_node->next = token_list;
    token_list->prev = new_node;
    return new_node;
}

token_list_t *push_next(token_t *token, token_list_t *token_list)
{
    token_list_t *new_node = (token_list_t *)malloc(sizeof(token_list_t));
    new_node->token = token;
    token_list_t *prev_front = token_list->next;
    prev_front->prev = new_node;
    new_node->next = prev_front;
    new_node->prev = token_list;
    token_list->next = new_node;
    return new_node;
}

uint8_t remove_token(token_list_t *token_list)
{
    if (token_list->token == NULL)
        return 1;
    token_list_t *prev = (token_list_t *)token_list->prev;
    token_list_t *next = (token_list_t *)token_list->next;
    prev->next = next;
    next->prev = prev;
    delete_token(token_list->token);
    return 0;
}

inline token_list_t *push_back(token_t *token, token_list_t *token_list)
{
    return push_prev(token, get_head(token_list));
}

inline token_list_t *push_front(token_t *token, token_list_t *token_list)
{
    return push_next(token, get_head(token_list));
}

inline void delete_token(token_t *token)
{
    free(token->data);
    free(token);
}
