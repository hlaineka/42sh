/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:58:30 by helvi             #+#    #+#             */
/*   Updated: 2021/05/24 16:53:26 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "structs_21.h"
# include <stdbool.h>

# define BLANKS " \t\n\0"
# define OPCHARS "&;<>|"
# define REDIROPS "&<>|"
# define SPECIALPARAMS "@*#?-$!0~"
# define EXPANSIONCHARS "$`"
# define NODE_STACK_SIZE 20

/*
**enum e_token
**{	
**	tkn_token,				0
**	tkn_word, 				1
**	tkn_operator,			2
**	tkn_name,				3
**	tkn_assignment_word,	4
**	tkn_io_number,			5
**	tkn_and,				6
**	tkn_lpar,				7
**	tkn_rpar,				8
**	tkn_semi,				9
**	tkn_nl,					10
**	tkn_pipe,				11
**	tkn_less,				12
**	tkn_great,				13
**	tkn_and_if,				14
**	tkn_or_if,				15
**	tkn_dsemi,				16
**	tkn_dless,				17
**	tkn_dgreat,				18
**	tkn_lessand,			19
**	tkn_greatand,			20
**	tkn_lessgreat,			21
**	tkn_dlessdash,			22
**	tkn_clobber,			23
**	tkn_if,					24
**	tkn_then,				25
**	tkn_else,				26
**	tkn_elif,				27
**	tkn_fi,					28
**	tkn_do,					29
**	tkn_done,				30
**	tkn_case,				31
**	tkn_tesac,				32
**	tkn_while,				33
**	tkn_until,				34
**	tkn_for,				35
**	tkn_lbrace,				36
**	tkn_rbrace,				37
**	tkn_bang,				38
**	tkn_in,					39
**	tkn_redirop,			40
**	tkn_syntax_error		41
**	tkn_dash				42
**	tkn_eoi					43
};
*/

enum e_token
{	
	tkn_token,
	tkn_word,
	tkn_operator,
	tkn_name,
	tkn_assignment_word,
	tkn_io_number,
	tkn_and,
	tkn_lpar,
	tkn_rpar,
	tkn_semi,
	tkn_nl,
	tkn_pipe,
	tkn_less,
	tkn_great,
	tkn_and_if,
	tkn_or_if,
	tkn_dsemi,
	tkn_dless,
	tkn_dgreat,
	tkn_lessand,
	tkn_greatand,
	tkn_lessgreat,
	tkn_dlessdash,
	tkn_clobber,
	tkn_if,
	tkn_then,
	tkn_else,
	tkn_elif,
	tkn_fi,
	tkn_do,
	tkn_done,
	tkn_case,
	tkn_tesac,
	tkn_while,
	tkn_until,
	tkn_for,
	tkn_lbrace,
	tkn_rbrace,
	tkn_bang,
	tkn_in,
	tkn_redirop,
	tkn_syntax_error,
	tkn_dash,
	tkn_eoi
};

typedef struct s_token
{
	int				*quotes;
	bool			*quoted;
	int				maintoken;
	int				precedence;
	bool			left_associative;
	char			*value;
	struct s_token	*subtokens;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_node
{
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
	t_token			*subtokens;
	int				state;
	int				operation;
	char			*command;
}					t_node;

typedef t_job *(*t_op_function)(t_job *job, t_term *term, t_node *current);

/*
** parser/parser.c
*/

t_node				*parser(char *input, t_term *term);
void				debug_print_tree(t_node *node, char *prefix,
						int left_right);

/*
** parser/ast_creation/ast_builder.c
*/

t_node				*ast_builder(t_token *new_first);

/*
** parser/ast_creation/ast_creation.c
*/

t_node				*ast_creator(t_token *first, t_term *term);

/*
** parser/ast_creation/ast_functions.c
*/

t_node				*init_node(void);
int					is_unaryop(t_token *tkn);
void				free_ast(t_node *root);
void				free_nodestack(t_node *stack[]);

/*
** parser/ast_creation/precedence.c
*/

t_token				*add_precedence(t_token *first);

/*
** parser/ast_creation/shunting_yard.c
*/

t_token				*shunting_yard(t_token *first);

/*
** parser/tokenization/lexer.c
*/

t_token				*lexer(char *input, t_term *term);

/*
** parser/tokenization/advanced_tokenization.c
*/

t_token				*advanced_tokenization(t_token *first, t_term *term);

/*
** parser/tokenization/io_numbers.c
*/

t_token				*io_numbers(t_token *first);

/*
** parser/tokenization/operator_tokens_functions.c
*/
int					handle_tkn_io_number(t_token *current);
int					add_filename_tkn(t_token *current);

/*
** parser/tokenization/operator_tokens.c
*/

t_token				*validate_operator_tokens(t_token *first);

/*
** parser/tokenization/quote_removal.c
*/

void				quote_removal(t_token *first);

/*
** parser/tokenization/basic_token_functions.c
*/

t_token				*push_to_front(t_token *input, t_token *stack);
t_token				*push_to_end(t_token *input, t_token *output);
t_token				*delete_token(t_token *tkn);
void				free_tokens(t_token *tokens);
void				free_token(t_token *to_free);

/*
** parser/tokenization/basic_token_functions2.c
*/

t_token				*init_token(void);
t_token				*add_quotearray(t_token *current);
void				check_quotes(char c, bool *single_quoted,
						bool *double_quoted, bool *backslash);
void				check_backslash(char *str, char c, bool *backslash,
						bool single_quoted);

/*
** parser/tokenization/basic_token_functions3.c
*/

t_token				*add_subtoken(t_token *current, t_token *sub);
int					handle_operator_token(char *str, char *source, int *i,
						int *maintoken);
int					handle_word_token(char *str, char *source, int *i,
						int *maintoken);
void				free_tokens_sub(t_token *tokens);
int					*init_quotearray(t_token *current);

/*
** parser/tokenization/basic_tokens.c
*/

t_token				*define_basic_tokens(char *input);

/*
** parser/tokenization/tilde_expansion.c
*/

int					tilde_expansion(t_token *tkn, t_term *term, int tilde);

/*
** parser/tokenization/dollar_expansion.c
*/

int					dollar_expansion(t_token *tkn, t_term *term, int dollar);

/*
** parser/tokenization/word_expansion.c
*/

t_token				*word_expansions(t_token *first, t_term *term);

#endif
