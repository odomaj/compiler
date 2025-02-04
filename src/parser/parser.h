#ifndef COMPILER_PARSER_PARSER_H
#define COMPILER_PARSER_PARSER_H

#include "utils.h"

/* GRAMMAR
 * S  -> P S1
 * S1 -> '+' P S1 | '-' P S1 | empty
 * P  -> E P1
 * P1 -> '*' E P1 | '/' E P1 | empty
 * E  -> B E1
 * E1 -> '^' E | empty
 * B  -> '(' S ')' | int
 */

typedef struct
{
    int8_t return_code;
    float result;
} parser_data_t;

parser_data_t parse_tree(token_list_t *tree);

parser_data_t sum(token_list_t *tree);
parser_data_t sum_help(token_list_t *tree);
parser_data_t product(token_list_t *tree);
parser_data_t product_help(token_list_t *tree);
parser_data_t power(token_list_t *tree);
parser_data_t power_help(token_list_t *tree);
parser_data_t bracket(token_list_t *tree);

#endif
