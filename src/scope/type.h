#ifndef COMPILER_COMMON_SCOPE_TYPE_H
#define COMPILER_COMMON_SCOPE_TYPE_H

#include <stdint.h>

#define TYPE_STANDARD 0
#define TYPE_ARRAY 1

#define TYPE_EMPTY 0
#define TYPE_INT 1
#define TYPE_REAL 2

typedef struct
{
    uint8_t type;
} type_standard_t;

typedef struct
{
    int start_i;
    int end_i;
} type_array_t;

typedef struct
{
    uint8_t type_class;

    type_standard_t standard;
    type_array_t array;
} type_t;

#endif
