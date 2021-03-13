/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 11:58:30 by helvi             #+#    #+#             */
/*   Updated: 2021/03/13 17:06:48 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "21sh.h"

enum e_token
{	token,
	word,
	name,
	assignment_word,
	io_number,
	and,
	lpar,
	rpar,
	semi,
	tkn_nl,
	tkn_pipe,
	less,
	great,
	and_if,
	or_if,
	dsemi,
	dless,
	dgreat,
	lessand,
	greatand,
	lessgreat,
	dlessdash,
	clobber,
	tif,
	tthen,
	telse,
	telif,
	tfi,
	tdo,
	tdone,
	tcase,
	ttesac,
	twhile,
	tuntil,
	tfor,
	tlbrace,
	trbrace,
	tbang,
	tin,
	teoi
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
}					t_token;


t_job				*parser(char *input);