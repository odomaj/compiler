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

%type <tval> identifier_list
%type <tval> declarations
%type <tval> type
%type <tval> range
%type <tval> standard_type
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
		{ *tree = tree_rule( TREE_PROGRAM, RULE_1, $4, tree_rule( TREE_PROGRAM, RULE_1, $7, tree_rule( TREE_PROGRAM, RULE_1, $8, $9 ) ) ); }
	;

identifier_list
	: NAME
		{
			if( search_scope_depth( scope, $1, 0 ) != NULL)
			{
				yyerror(tree, scope, "variable redeclared");
				YYABORT;
			}
			$$ = tree_rule( TREE_IDENTIFIER_LIST, RULE_1, NULL, tree_sym( insert_scope( scope, $1 ) ) );
		}
	| identifier_list COMMA NAME
		{
			if( search_scope_depth( scope, $3, 0 ) != NULL)
			{
				yyerror(tree, scope, "variable redeclared");
				YYABORT;
			}
			$$ = tree_rule( TREE_IDENTIFIER_LIST, RULE_2, $1, tree_sym( insert_scope( scope, $3 ) ) );
		}
	;

declarations
	: /* empty */
		{ $$ = tree_rule( TREE_DECLARATIONS, RULE_1, NULL, NULL ); }
	| declarations VAR identifier_list COLON type SEMICOLON
		{
			(void)declare_types( $3, $5 );
			$$ = tree_rule( TREE_DECLARATIONS, RULE_2, $1, tree_rule( TREE_DECLARATIONS, RULE_2, $3, $5 ) );
		}
	;

type
	: standard_type
		{ $$ = tree_rule( TREE_TYPE, RULE_1, NULL, $1 ); }
	| ARRAY OPEN_B range CLOSE_B OF standard_type
		{ $$ = tree_rule( TREE_TYPE, RULE_2, $3, $6 ); }
	;

range
	: INUM DOTOP INUM
		{ $$ = tree_rule( TREE_RANGE, RULE_1, tree_inum( $1 ), tree_inum( $3 ) ); }
	;

standard_type
	: INTEGER
		{ $$ = tree_rule( TREE_STANDARD_TYPE, RULE_1, NULL, tree_type( TYPE_INT ) ); }
	| REAL
		{ $$ = tree_rule( TREE_STANDARD_TYPE, RULE_2, NULL, tree_type( TYPE_REAL ) ); }
	;

subprogram_declarations
	: /* empty */
		{ $$ = tree_rule( TREE_SUBPROGRAM_DECLARATIONS, RULE_1, NULL, NULL ); }
	| subprogram_declarations subprogram_declaration SEMICOLON
		{ $$ = tree_rule( TREE_SUBPROGRAM_DECLARATIONS, RULE_2, $1, $2 ); }
	;

subprogram_declaration
	:
	{
		scope = push_scope( scope );
		assert(scope != NULL);
		scope_depth++;
	}
	subprogram_header
	declarations
	subprogram_declarations
	compound_statement
		{
			if( check_subprogram( $2, scope ) )
			{
				yyerror(tree, scope, "function missing return or statement has return");
				YYABORT;
			}
			$$ = tree_rule( TREE_SUBPROGRAM_DECLARATION, RULE_1, $2, tree_rule( TREE_SUBPROGRAM_DECLARATION, RULE_1, $3, tree_rule( TREE_SUBPROGRAM_DECLARATION, RULE_1, $4, $5 ) ) );
			scope = pop_scope( scope );
			scope_depth--;
		}
	;

subprogram_header
	: FUNCTION NAME arguments COLON standard_type SEMICOLON
		{
			if( search_scope_depth( scope->upper_scope, $2, scope_depth ) != NULL)
			{
				yyerror(tree, scope, "variable redeclared as function");
				YYABORT;
			}
			list_t *func_sym = insert_scope_fun( scope->upper_scope, $2, CLASS_FUNCTION );
			(void)type_func( func_sym, $5 );
			$$ = tree_rule( TREE_SUBPROGRAM_HEADER, RULE_1, tree_sym( func_sym ), tree_rule( TREE_SUBPROGRAM_HEADER, RULE_1, $3, $5 ) );
		}
	| PROCEDURE NAME arguments SEMICOLON
		{
			if( search_scope_depth( scope->upper_scope, $2, scope_depth ) != NULL)
			{
				yyerror(tree, scope, "variable redeclared as procedure");
				YYABORT;
			}
			$$ = tree_rule( TREE_SUBPROGRAM_HEADER, RULE_2, tree_sym( insert_scope_fun( scope->upper_scope, $2, CLASS_PROCEDURE ) ), $3);
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
		{
			(void)declare_types( $1, $3 );
			$$ = tree_rule( TREE_PARAMETER_LIST, RULE_1, $1, $3 );
		}
	| parameter_list SEMICOLON identifier_list COLON type
		{
			(void)declare_types( $3, $5 );
			$$ = tree_rule( TREE_PARAMETER_LIST, RULE_2, $1, tree_rule( TREE_PARAMETER_LIST, RULE_2, $3, $5 ) );
		}
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
		{
			if( try_update_return( interpret_var( $1 ), $3 ) )
			{
				yyerror( tree, scope, "function returning incorrect type" );
				YYABORT;
			}
			$$ = tree_rule( TREE_STATEMENT, RULE_1, $1, $3 );
		}
	| procedure_statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_2, NULL, $1 ); }
	| compound_statement
		{ $$ = tree_rule( TREE_STATEMENT, RULE_3, NULL, $1 ); }
	| IF expression THEN statement ELSE statement
		{
			if( !is_standard_type( $2 ) )
			{
				yyerror( tree, scope, "test expression not a standard type" );
				YYABORT;
			}
			$$ = tree_rule( TREE_STATEMENT, RULE_3, $2, tree_rule( TREE_STATEMENT, RULE_3, $4, $6 ) );
		}
	| IF expression THEN statement
		{
			if( !is_standard_type( $2 ) )
			{
				yyerror( tree, scope, "test expression not a standard type" );
				YYABORT;
			}
			$$ = tree_rule( TREE_STATEMENT, RULE_4, $2, $4 );
		}
	| WHILE expression DO statement
		{
			if( !is_standard_type( $2 ) )
			{
				yyerror( tree, scope, "test expression not a standard type" );
				YYABORT;
			}
			$$ = tree_rule( TREE_STATEMENT, RULE_5, $2, $4 );
		}
	| REPEAT statement UNTIL expression
		{
			if( !is_standard_type( $4 ) )
			{
				yyerror( tree, scope, "test expression not a standard type" );
				YYABORT;
			}
			$$ = tree_rule( TREE_STATEMENT, RULE_5, $2, $4 );
		}
	| FOR NAME ASSOP range DO statement
		{
			list_t *symbol = search_scope_depth( scope, $2, scope_depth );
			if( symbol == NULL )
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			if( !symbol_is_int( symbol ) )
			{
				yyerror(tree, scope, "non integer type used in for loop");
				YYABORT;
			}
			$$ = tree_rule( TREE_STATEMENT, RULE_6, tree_sym( symbol ), tree_rule( TREE_STATEMENT, RULE_6, $4, $6 ) );
		}
	| FOR NAME ASSOP INUM TO INUM DO statement
		{
			list_t *symbol = search_scope_depth( scope, $2, scope_depth );
			if( symbol == NULL )
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			if( !symbol_is_int( symbol ) )
			{
				yyerror(tree, scope, "non integer type used in for loop");
				YYABORT;
			}
			$$ = tree_rule( TREE_STATEMENT, RULE_7, tree_sym( symbol ), tree_rule( TREE_STATEMENT, RULE_7, tree_inum( $4 ), tree_rule( TREE_STATEMENT, RULE_7, tree_inum( $6 ), $8 ) ) );
		}
	;

variable
	: NAME
		{
			if( search_scope_depth( scope, $1, scope_depth ) == NULL)
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			$$ = tree_rule( TREE_VARIABLE, RULE_1, NULL, tree_sym( search_scope_depth( scope, $1, scope_depth ) ) );
		}
	| NAME OPEN_B expression CLOSE_B
		{
			if( search_scope_depth( scope, $1, scope_depth ) == NULL)
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			if( check_int( $3 ) )
			{
				yyerror(tree, scope, "non integer type used for indexing array");
				YYABORT;
			}
			$$ = tree_rule( TREE_VARIABLE, RULE_2, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 );
		}
	;

procedure_statement
	: NAME
		{
			if( search_scope_depth( scope, $1, scope_depth ) == NULL)
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			$$ = tree_rule( TREE_PROCEDURE_STATEMENT, RULE_1, NULL, tree_sym( search_scope_depth( scope, $1, scope_depth ) ) );
		}
	| NAME OPEN_P expression_list CLOSE_P
		{
			if( search_scope_depth( scope, $1, scope_depth ) == NULL)
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			$$ = tree_rule( TREE_PROCEDURE_STATEMENT, RULE_2, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 );
		}
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
		{
			if( mismatched_types( $1, $3 ) )
			{
				yyerror(tree, scope, "mismatched types");
				YYABORT;
			}
			$$ = tree_rule( TREE_EXPRESSION, RULE_2, NULL, tree_op( TREE_RELOP, yylval.opval, $1, $3 ) );
		}
	;

simple_expression
	: term
		{ $$ = tree_rule( TREE_SIMPLE_EXPRESSION, RULE_1, NULL, $1 ); }
	| ADDOP term
		{ $$ = tree_rule( TREE_SIMPLE_EXPRESSION, RULE_2, NULL, tree_op( TREE_ADDOP, yylval.opval, NULL, $2 ) ); }
	| simple_expression ADDOP term
		{
			if( mismatched_types( $1, $3 ) )
			{
				yyerror(tree, scope, "mismatched types");
				YYABORT;
			}
			$$ = tree_rule( TREE_SIMPLE_EXPRESSION, RULE_3, NULL, tree_op( TREE_ADDOP, yylval.opval, $1, $3 ) );
		}
	;

term
	: factor
		{ $$ = tree_rule( TREE_TERM, RULE_1, NULL, $1 ); }
	| term MULOP factor
		{
			if( mismatched_types( $1, $3 ) )
			{
				yyerror(tree, scope, "mismatched types");
				YYABORT;
			}
			$$ = tree_rule( TREE_TERM, RULE_2, NULL, tree_op( TREE_MULOP, yylval.opval, $1, $3 ) );
		}
	;

factor
	: NAME
		{
			if( search_scope_depth( scope, $1, scope_depth ) == NULL)
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			$$ = tree_rule( TREE_FACTOR, RULE_1, NULL, tree_sym( search_scope_depth( scope, $1, scope_depth ) ) );
		}
	| NAME OPEN_P expression_list CLOSE_P
		{
			if( search_scope_depth( scope, $1, scope_depth ) == NULL)
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			$$ = tree_rule( TREE_FACTOR, RULE_2, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 );
		}
	| NAME OPEN_B expression CLOSE_B
		{
			if( search_scope_depth( scope, $1, scope_depth ) == NULL)
			{
				yyerror(tree, scope, "variable used before declared");
				YYABORT;
			}
			if( check_int( $3 ) )
			{
				yyerror(tree, scope, "non integer type used for indexing array");
				YYABORT;
			}
			$$ = tree_rule( TREE_FACTOR, RULE_3, tree_sym( search_scope_depth( scope, $1, scope_depth ) ), $3 );
		}
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
