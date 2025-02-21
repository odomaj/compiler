#ifndef COMPILER_TREE_TREE_H
#define COMPILER_TREE_TREE_H

#include <stdint.h>
#include "list.h"

/* types */

#define INUM 0
#define FNUM 1
#define NAME 2
#define ARRAY 3
#define FUNCTION 4
#define COMPOP 5
#define ADDOP 6
#define IF 7
#define WHILE 8
#define FOR 9
#define ASSIGNOP 10
#define COMMA 11

typedef struct tree_s
{
    uint8_t type;
    union
    {
        int ival;
        float fval;
        list_t *sval;
        int op_val;
    } value;

    struct tree_s *left;
    struct tree_s *right;

} tree_t;

#endif
