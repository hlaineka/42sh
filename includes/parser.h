/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:58:30 by helvi             #+#    #+#             */
/*   Updated: 2021/03/17 09:13:28 by helvi            ###   ########.fr       */
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

enum e_token
{	tkn_token,
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
	tkn_essand,
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

/*
** word delimiters:
** meta_space = ' '
** meta_tab = ascii 9
** meta_nl, = ascii 10
** meta_verbar = '|'
** meta_amp = '&'
** meta_semi = ':'
** meta_lpar = '('
** meta_rpar = ')'
** meta_less = '<'
** meta_great = '>'
**enum e_metachars
**{	meta_space ,
**	meta_tab,
**	meta_nl,
**	meta_verbar,
**	meta_amp,
**	meta_semi,
**	meta_lpar,
**	meta_rpar,
**	meta_less,
**	meta_great
**};
*/

typedef struct 		s_token
{
	int				token;
	char			*value;
	bool			single_quoted;
	bool			double_quoted;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;


t_job				*parser(char *input);

/*
** lexer.c
*/

t_token				*lexer(char *input);

/*
** tokens.c
*/

t_token				*get_token(char *delimiters, char **source);

#endif
