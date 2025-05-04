#ifndef COMPILER_TREE_TREE_H
#define COMPILER_TREE_TREE_H

#include <stdint.h>

#include "list.h"
#include "scope.h"
#include "type.h"

#define IVAL 0
#define RVAL 1
#define SVAL 2
#define OPVAL 3
#define RULE_VAL 4
#define TVAL 5

#define TREE_PROGRAM 0
#define TREE_IDENTIFIER_LIST 1
#define TREE_DECLARATIONS 2
#define TREE_TYPE 3
#define TREE_RANGE 4
#define TREE_STANDARD_TYPE 5
#define TREE_SUBPROGRAM_DECLARATIONS 6
#define TREE_SUBPROGRAM_DECLARATION 7
#define TREE_SUBPROGRAM_HEADER 8
#define TREE_ARGUMENTS 9
#define TREE_PARAMETER_LIST 10
#define TREE_COMPOUND_STATEMENT 11
#define TREE_OPTIONAL_STATEMENTS 12
#define TREE_STATEMENT_LIST 13
#define TREE_STATEMENT 14
#define TREE_VARIABLE 15
#define TREE_PROCEDURE_STATEMENT 16
#define TREE_EXPRESSION_LIST 17
#define TREE_EXPRESSION 18
#define TREE_SIMPLE_EXPRESSION 19
#define TREE_TERM 20
#define TREE_FACTOR 21

#define RULE_1 0
#define RULE_2 1
#define RULE_3 2
#define RULE_4 3
#define RULE_5 4
#define RULE_6 5
#define RULE_7 6

#define TREE_RELOP 0
#define TREE_ADDOP 1
#define TREE_MULOP 2

typedef struct
{
    uint8_t class;
    uint8_t value;
} operator_t;

typedef struct
{
    uint8_t rule;
    uint8_t option;
} rule_t;

typedef struct tree_s
{
    uint8_t type;
    uint8_t label;
    union
    {
        int ival;
        float rval;
        list_t *sval;
        operator_t op_val;
        rule_t rule_val;
        type_standard_t tval;
    } value;

    struct tree_s *left;
    struct tree_s *right;
} syntax_tree_t;

syntax_tree_t *tree_inum(int ival);
syntax_tree_t *tree_rnum(float rval);
syntax_tree_t *tree_op(uint8_t type, uint8_t value, syntax_tree_t *left, syntax_tree_t *right);
syntax_tree_t *tree_sym(list_t *sval);
syntax_tree_t *tree_rule(uint8_t rule, uint8_t option, syntax_tree_t *left, syntax_tree_t *right);
syntax_tree_t *tree_type(uint8_t type);

void free_tree(syntax_tree_t *tree);

type_t tree_to_type(syntax_tree_t *tree);
type_t tree_to_stype(syntax_tree_t *tree);
type_array_t tree_to_atype(syntax_tree_t *tree);

void declare_types(syntax_tree_t *id_list, syntax_tree_t *type);
void declare_type(syntax_tree_t *id, type_t type);

void declare_arg_types(syntax_tree_t *param_list, syntax_tree_t *s_type);

uint8_t mismatched_types(syntax_tree_t *left, syntax_tree_t *right);
uint8_t symbol_is_int(list_t *symbol);
uint8_t check_int(syntax_tree_t *tree);
uint8_t is_standard_type(syntax_tree_t *tree);
uint8_t type_check(type_t a, type_t b);

type_t get_saved_type(syntax_tree_t *tree);

type_t expression_type(syntax_tree_t *tree);
type_t simple_expression_type(syntax_tree_t *tree);
type_t term_type(syntax_tree_t *tree);
type_t factor_type(syntax_tree_t *tree);

uint8_t check_subprogram(syntax_tree_t *tree, scope_t *scope);

list_t *interpret_var(syntax_tree_t *tree);
list_t *get_sym(syntax_tree_t *tree);

void try_update_return(list_t *list, syntax_tree_t *tree);

#endif
