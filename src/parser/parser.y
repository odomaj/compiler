%{

#include <stdlib.h>
#include <assert.h>

#include "parser.h"

extern FILE *yyin;
size_t scope_depth = 0;

%}

%union
{
	/*
	 *	scanner fields
	 */

	// INUM value
	int ival;

	// RNUM value
	float rval;

	// RELOP ADDOP MULOP value
	int opval;

	// NAME value
	char *sval;

	/*
	 *	semantic fields
	 */

	// syntax tree value
	syntax_tree_t *tval;
	list_t *lval;
	type_t ttype;
	type_array_t atype;
	type_standard_t stype;
}

%parse-param { syntax_tree_t **tree } { scope_t *scope }

%token PROGRAM FUNCTION PROCEDURE
%token VAR ARRAY OF
%token INTEGER REAL
%token BBEGIN END
%token IF THEN ELSE
%token WHILE DO
%token REPEAT UNTIL
%token FOR TO

%token <ival> INUM
%token <rval> RNUM
%token <sval> NAME

%token <opval> RELOP
%token <opval> ADDOP
%token <opval> MULOP

%token LT LE GT GE EQ NE
%token PLUS MINUS OR
%token STAR SLASH MOD DIV AND
%token NOT
%token ASSOP
%token DOTOP

%token COMMA LOCAL PARAMETER

%token OPEN_P CLOSE_P
%token OPEN_B CLOSE_B
%token SEMICOLON COLON DOT

%token ERR

%type <lval> identifier_list
%type <lval> declarations
%type <ttype> type
%type <atype> range
%type <stype> standard_type
%type <tval> subprogram_declarations
%type <tval> subprogram_declaration
%type <tval> subprogram_header
%type <tval> arguments
%type <tval> parameter_list
%type <tval> compound_statement
%type <tval> optional_statements
%type <tval> statement_list
%type <tval> statement
%type <tval> variable
%type <tval> procedure_statement
%type <tval> expression_list
%type <tval> expression
%type <tval> simple_expression
%type <tval> term
%type <tval> factor

%%

program
	: PROGRAM NAME OPEN_P identifier_list CLOSE_P SEMICOLON
	declarations
	subprogram_declarations
	compound_statement
	DOT
		{
			if ( insert_scope_l( scope, $7 ) || insert_scope_l( scope, $4 ))
			{
				yyerror( tree, scope, "variable redeclared" );
				YYABORT;
			}
			*tree = tree_rule( TREE_PROGRAM, RULE_1, $8, $9 );
		}
	;

identifier_list
	: NAME
		{
			$$ = new_list( $1 );
		}
	| identifier_list COMMA NAME
		{
			$$ = insert_list( $1, $3 );
		}
	;

declarations
	: /* empty */
		{ $$ = NULL; }
	| declarations VAR identifier_list COLON type SEMICOLON
		{
			(void)type_list( $3, $5 );
			$$ = $3 ;
		}
	;

type
	: standard_type
		{
			$$.type_class = TYPE_STANDARD;
			$$.standard = $1;
		}
	| ARRAY OPEN_B range CLOSE_B OF standard_type
		{
			$$.type_class = TYPE_ARRAY;
			$$.standard = $6;
			$$.array = $3;
		}
	;

range
	: INUM DOTOP INUM
		{
			$$.start_i = $1; 
			$$.end_i = $3;
		}
	;

standard_type
	: INTEGER
		{ $$.type = TYPE_INT; }
	| REAL
		{ $$.type = TYPE_REAL; }
	;

subprogram_declarations
	: /* empty */
		{ $$ = tree_rule( TREE_SUBPROGRAM_DECLARATIONS, RULE_1, NULL, NULL ); }
	| subprogram_declarations subprogram_declaration SEMICOLON
		{ $$ = tree_rule( TREE_SUBPROGRAM_DECLARATIONS, RULE_2, $1, $2 ); }
	;

subprogram_declaration
	: subprogram_header
	declarations
	subprogram_declarations
	compound_statement
		{
			if ( insert_scope_l( scope, $2 ) )
			{
				yyerror( tree, scope, "variable redeclared" );
				YYABORT;
			}
			$$ = tree_rule( TREE_SUBPROGRAM_DECLARATION, RULE_1, $1, tree_rule( TREE_SUBPROGRAM_DECLARATION, RULE_1, $3, $4 ) );
		}
	;

subprogram_header
	: FUNCTION NAME arguments COLON standard_type SEMICOLON
		{
			if( search_scope_depth( scope, $2, scope_depth ) != NULL)
			{
				yyerror(tree, scope, "variable redeclared as function");
				YYABORT;
			}
			$$ = tree_rule( TREE_SUBPROGRAM_HEADER, RULE_1, tree_sym( insert_scope( scope, $2 ) ), tree_rule( TREE_SUBPROGRAM_HEADER, RULE_1, $3, $5 ) );
		}
	| PROCEDURE NAME arguments SEMICOLON
		{
			if( search_scope_depth( scope, $2, scope_depth ) != NULL)
			{
				yyerror(tree, scope, "variable redeclared as procedure");
				YYABORT;
			}
			$$ = tree_rule( TREE_SUBPROGRAM_HEADER, RULE_2, tree_sym( insert_scope( scope, $2 ) ), $3);
		}
	;

arguments
	: /* empty */
		{ $$ = tree_rule( TREE_ARGUMENTS, RULE_1, NULL, NULL ); }
	| OPEN_P parameter_list CLOSE_P
		{ $$ = tree_rule( TREE_ARGUMENTS, RULE_2, NULL, $2 ); }
	;

parameter_list
	: identifier_list COLON type
		{ $$ = tree_rule( TREE_PARAMETER_LIST, RULE_1, $1, $3 ); }
	| parameter_list SEMICOLON identifier_list COLON type
		{ $$ = tree_rule( TREE_PARAMETER_LIST, RULE_2, $1, tree_rule( TREE_PARAMETER_LIST, RULE_2, $3, $5 ) ); }
	;

compound_statement
	: BBEGIN optional_statements END
		{ $$ = tree_rule( TREE_COMPOUND_STATEMENT, RULE_1, NULL, $2 ); }
	;

optional_statements
	: /* empty */
		{ $$ = tree_rule( TREE_OPTIONAL_STATEMENTS, RULE_1, NULL, NULL ); }
	| statement_list
		{ $$ = tree_rule( TREE_OPTIONAL_STATEMENTS, RULE_2, NULL, $1 ); }
	;

statement_list
	: statement
		{ $$ = tree_rule( TREE_STATEMENT_LIST, RULE_1, NULL, $1 ); }
	| statement_list SEMICOLON statement
		{ $$ = tree_rule( TREE_STATEMENT_LIST, RULE_2, $1, $3 ); }
	;

statement
	: variable ASSOP expression
		{ $$ = tree_rule( TREE_STATEMENT, RULE_1, $1, $3 ); }
	| procedure_statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_2, NULL, $1 ); }
	| compound_statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_3, NULL, $1 ); }
	| IF expression THEN statement ELSE statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_3, $2, tree_rule( TREE_STATEMENT, RULE_3, $4, $6 ) ); }
	| IF expression THEN statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_4, $2, $4 ); }
	| WHILE expression DO statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_5, $2, $4 ); }
	| REPEAT statement UNTIL expression
		{ $$ = tree_rule( TREE_STATEMENT, RULE_5, $2, $4 ); }
	| FOR NAME ASSOP range DO statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_6, tree_sym( search_scope_depth( scope, $2, scope_depth ) ), tree_rule( TREE_STATEMENT, RULE_6, $4, $6 ) ) ; }
	| FOR NAME ASSOP INUM TO INUM DO statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_7, tree_sym( search_scope_depth( scope, $2, scope_depth ) ), tree_rule( TREE_STATEMENT, RULE_7, tree_inum( $4 ), tree_rule( TREE_STATEMENT, RULE_7, tree_inum( $6 ), $8 ) ) ) ; }
	;

variable
	: NAME
		{ $$ = tree_rule( TREE_VARIABLE, RULE_1, NULL, tree_sym( search_scope_depth( scope, $1, scope_depth ) ) ); }
	| NAME OPEN_B expression CLOSE_B
		{ $$ = tree_rule( TREE_VARIABLE, RULE_2, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 ); }
	;

procedure_statement
	: NAME
		{ $$ = tree_rule( TREE_PROCEDURE_STATEMENT, RULE_1, NULL, tree_sym( search_scope_depth( scope, $1, scope_depth ) ) ); }
	| NAME OPEN_P expression_list CLOSE_P
		{ $$ = tree_rule( TREE_PROCEDURE_STATEMENT, RULE_2, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 ); }
	;

expression_list
	: expression
		{ $$ = tree_rule( TREE_EXPRESSION_LIST, RULE_1, NULL, $1 ); }
	| expression_list COMMA expression
		{ $$ = tree_rule( TREE_EXPRESSION_LIST, RULE_2, $1, $3 ); }
	;

expression
	: simple_expression
		{ $$ = tree_rule( TREE_EXPRESSION, RULE_1, NULL, $1 ); }
	| simple_expression RELOP simple_expression
		{ $$ = tree_rule( TREE_EXPRESSION, RULE_2, NULL, tree_op( TREE_RELOP, yylval.opval, $1, $3 ) ); }
	;

simple_expression
	: term
		{ $$ = tree_rule( TREE_SIMPLE_EXPRESSION, RULE_1, NULL, $1 ); }
	| ADDOP term
		{ $$ = tree_rule( TREE_SIMPLE_EXPRESSION, RULE_2, NULL, tree_op( TREE_ADDOP, yylval.opval, NULL, $2 ) ); }
	| simple_expression ADDOP term
		{ $$ = tree_rule( TREE_SIMPLE_EXPRESSION, RULE_3, NULL, tree_op( TREE_ADDOP, yylval.opval, $1, $3 ) ); }
	;

term
	: factor
		{ $$ = tree_rule( TREE_TERM, RULE_1, NULL, $1 ); }
	| term MULOP factor
		{ $$ = tree_rule( TREE_TERM, RULE_2, NULL, tree_op( TREE_MULOP, yylval.opval, $1, $3 ) ); }
	;

factor
	: NAME
		{ $$ = tree_rule( TREE_FACTOR, RULE_1, NULL, tree_sym( search_scope_depth( scope, $1, scope_depth ) ) ); }
	| NAME OPEN_P expression_list CLOSE_P
		{ $$ = tree_rule( TREE_FACTOR, RULE_2, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 ); }
	| NAME OPEN_B expression CLOSE_B
		{ $$ = tree_rule( TREE_FACTOR, RULE_3, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 ); }
	| INUM
		{ $$ = tree_rule( TREE_FACTOR, RULE_4, NULL, tree_inum( $1 ) ); }
	| RNUM
		{ $$ = tree_rule( TREE_FACTOR, RULE_5, NULL, tree_rnum( $1 ) ); }
	| OPEN_P expression CLOSE_P
		{ $$ = tree_rule( TREE_FACTOR, RULE_6, NULL, $2 ); }
	| NOT factor
		{ $$ = tree_rule( TREE_FACTOR, RULE_7, NULL, $2 ); }
	;

%%

// for semantic checks YYABORT reports failure

int parse(const char *file_path, syntax_tree_t** tree_dest, scope_t **symbol_dest)
{
	yyin = fopen(file_path, "r");
	if(yyin == NULL)
	{
		fprintf(stderr, "[ERROR] %s not found\n", file_path);
		return 1;
	}

	*symbol_dest = make_scope(NULL);

	int out = yyparse(tree_dest, *symbol_dest);
	fclose(yyin);

	return out;
}
