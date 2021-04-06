/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:58:30 by helvi             #+#    #+#             */
/*   Updated: 2021/04/06 11:23:10 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

//# include "includes.h"
# include "structs_21.h"
# include <stdbool.h>

# define METACHARS "|&;()<> \t\n"
# define OPCHARS "|&;()<>"
# define SPECIALPARAMS "@*#?-$!0"
# define EXPANSIONCHARS "~$`"

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
**	tkn_eoi					40
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
	tkn_eoi
};

typedef struct s_token
{
	int				*tokens;
	int				maintoken;
	int				precedence;
	bool			left_associative;
	char			*value;
	bool			single_quoted;
	bool			double_quoted;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_node
{
	struct s_node	*parent;
	struct s_node	*left;
	struct s_node	*right;
	int				state;
	int				operation;
	char			**envp;
	char			**argv;
	int				argc;
	int				stdin;
	int				stdout;
	int				stderr;
	char			*command;
	int				pid;
	bool			completed;
	bool			stopped;
	int				status;
}					t_node;

typedef int(*t_op_function)(t_token **stack, t_job *executable);

t_node				*parser(char *input, bool debug);
void				debug_print_tree(t_node *node, char *prefix);

/*
** lexer.c
*/

t_token				*lexer(char *input);

/*
** tokens.c
*/

t_token				*get_basic_token(char *delimiters, char **source);

/*
** token_functions.c
*/

t_token				*push_to_front(t_token *input, t_token *stack);
t_token				*push_to_end(t_token *input, t_token *output);
t_token				*delete_token(t_token *tkn);
void				free_tokens(t_token *tokens);
void				free_token(t_token *to_free);

/*
** ast_creation.c
*/

t_node				*ast_creator(t_token *first, bool debug);

/*
** precedence.c
*/

t_token				*add_precedence(t_token *first);

/*
** shunting_yard.c
*/

t_token				*shunting_yard(t_token *first);

/*
** quote_removal.c
*/

void				quote_removal(t_token *first);

/*
** ast_builder.c
*/

t_node				*ast_builder(t_token *new_first);

/*
** free_ast.c
*/

void				free_ast(t_node *root);

/*
** operator_tokens.c
*/

t_token				*define_operator_tokens(t_token *first);

/*
** operator_tokens_functions.c
*/
void				check_tkn_quotes(t_token *current);

#endif
