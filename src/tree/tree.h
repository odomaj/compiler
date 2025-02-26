#ifndef COMPILER_TREE_TREE_H
#define COMPILER_TREE_TREE_H

#include <stdint.h>
#include "list.h"

/*
#define PROGAM 0
#define PROCEDURE 1
#define FUNCTION 2
#define VAR 3
#define ARRAY 4
#define OF 5
#define BBEGIN 6
#define END 7
#define INTEGER 8
#define REAL 9
#define IF 10
#define THEN 11
#define ELSE 12
#define WHILE 13
#define DO 14
#define FOR 15
#define TO 16
#define RELOP 17
#define ADDOP 18
#define MULOP 19
#define NOT 20
#define ASSOP 21
#define DOTOP 22
#define INUM 23
#define RNUM 24
#define NAME 25
#define ERR 26
#define COMMA 27

#define LT 0
#define LE 1
#define GT 2
#define GE 3
#define EQ 4
#define NE 5

#define PLUS 0
#define MINUS 1
#define OR 2

#define STAR 0
#define SLASH 1
#define DIV 2
#define MOD 3
#define AND 4
*/

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
