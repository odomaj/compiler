#include "scanner.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t scan_file(const char *src_file_path, token_list_t *dest)
{
    FILE *file = fopen(src_file_path, "r");
    if (file == NULL)
    {
        fprintf(stderr, "unable to open file to scan: %s\n", src_file_path);
        return 1;
    }
    int c = 0;
    uint16_t index = 0;
    uint8_t prev_type = NO_TYPE;
    char buff[SCANNER_BUFF_SIZE];
    while ((buff[index] = fgetc(file)) != EOF)
    {
        token_t *new_token = token_buff(buff, &index, &prev_type);
        index++;
        if (new_token != NULL)
            push_prev(new_token, dest);
    }
    switch (prev_type)
    {
    case NO_TYPE:
        break;
    case OPERATOR:
        push_prev(new_token(OPERATOR, buff), dest);
        break;
    case INT:
        int num = atoi(buff);
        push_prev(new_token(INT, &num), dest);
        break;
    }
    fclose(file);
    return 0;
}

token_t *token_buff(char *buff, uint16_t *index, uint8_t *prev_type)
{
    char last_char = buff[*index];
    if (last_char >= '0' && last_char <= '9')
    {
        switch (*prev_type)
        {
        case NO_TYPE:
        case INT:
            *prev_type = INT;
            return NULL;
        case OPERATOR:
            *prev_type = INT;
            token_t *token = new_token(OPERATOR, buff);
            buff[0] = buff[1];
            *index = 0;
            return token;
        }
    }
    switch (last_char)
    {
    case '+':
    case '-':
    case '*':
    case '/':
        switch (*prev_type)
        {
        case NO_TYPE:
            *prev_type = OPERATOR;
            return NULL;
        case OPERATOR:
            return NULL;
        case INT:
            *prev_type = OPERATOR;
            int num = atoi(buff);
            buff[0] = last_char;
            *index = 0;
            return new_token(INT, &num);
        }
    }
    (*index)--;
    return NULL;
}
