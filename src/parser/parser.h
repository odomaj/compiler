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
 * B  -> '(' S ')' | NUM
 */

tree_t *parse_file(const char *filepath);

tree_t *sum();
tree_t *sum_help();

tree_t *product();
tree_t *product_help();

tree_t *power();
tree_t *power_help();

tree_t *bracket();
tree_t *bracket_help();

#endif
