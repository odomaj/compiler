#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "scanner.h"

FILE *file = NULL;

char *buffer = NULL;
size_t buffer_size = 0;
size_t buffer_end = 0;

uint8_t previous_token_type = NO_TYPE;

uint8_t open_scanner(const char *filepath)
{
    file = fopen(filepath, "r");
    if (file == NULL)
        return 0;
    buffer_size = DEFAULT_BUFFER_SIZE;
    buffer = malloc(buffer_size * sizeof(char));
    return buffer != NULL;
}

uint8_t next_token(token_t *dest)
{
    if (file == NULL || buffer == NULL)
        return 1;
    if (buffer_end >= buffer_size && !resize_buffer())
        return 1;
    int c = 0;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r')
            continue;
        if (buffer_end >= buffer_size && !resize_buffer())
            return 0;
        buffer[buffer_end++] = (char)c;
        if (double_token())
            return first_token(dest);
    }
    return first_token(dest);
}

uint8_t double_token(void)
{
    uint8_t first_type = token_type(buffer[0], previous_token_type);
    if (first_type == NO_TYPE)
        return 1;
    uint8_t next_type = NO_TYPE;
    for (size_t i = 1; i < buffer_end; i++)
    {
        if (first_type != token_type(buffer[i], first_type))
            return 1;
    }
    return 0;
}

uint8_t token_type(char c, uint8_t previous_type)
{
    if (c <= '9' && c >= '0')
    {
        return NUM;
    }
    switch (c)
    {
    case '+':
    case '*':
    case '/':
    case '^':
        return OPERATOR;
    case '-':
        if (previous_type == NUM)
            return OPERATOR;
        return NUM;
    case '.':
        return NUM;
    }
    return NO_TYPE;
}

uint8_t first_token(token_t *dest)
{
    dest->type = token_type(buffer[0], previous_token_type);
    switch (dest->type)
    {
    case OPERATOR:
        (void)load_op(dest);
        break;
    case NUM:
        (void)load_num(dest);
        break;
    }
    return buffer_end != 0;
}

void load_op(token_t *dest)
{
    dest->data = malloc(sizeof(char));
    memcpy(dest->data, buffer, sizeof(char));

    previous_token_type = OPERATOR;
    buffer_end--;
    if (buffer_end == 0)
        return;
    memmove(buffer, &buffer[1], buffer_end);
}

void load_num(token_t *dest)
{
    // get index of next type (find char length of num)
    size_t next_type_index;
    for (next_type_index = 1; next_type_index <= buffer_end; next_type_index++)
    {
        if (token_type(buffer[next_type_index], NUM) != NUM)
            break;
    }

    // make numerical contents of buffer null terminated
    // save the numerical contents of buffer as double
    char temp = buffer[next_type_index];
    buffer[next_type_index] = '\0';
    double d = strtod(buffer, NULL);
    dest->data = malloc(sizeof(double));
    memcpy(dest->data, &d, sizeof(double));
    buffer[0] = temp;

    previous_token_type = NUM;
    buffer_end -= next_type_index;
    if (buffer_end < 2)
        return;
    memmove(&buffer[1], &buffer[next_type_index + 1], buffer_end - 1);
}

void close_scanner(void)
{
    if (file != NULL)
        fclose(file);
    file = NULL;
    (void)free(buffer);
    buffer = NULL;
    buffer_size = 0;
    buffer_end = 0;
}

uint8_t resize_buffer(void)
{
    size_t old_buffer_size = buffer_size;
    buffer_size += buffer_size;
    if (old_buffer_size >= buffer_size)
        return 0;
    return (buffer = realloc(buffer, buffer_size * sizeof(char))) != NULL;
}
