/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:44:33 by hlaineka          #+#    #+#             */
/*   Updated: 2021/10/10 10:37:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

/*
** Functions to handle dollar $ expansions. Currently only handles environment
** parameter substitution.
*/

static int	substitute_dollar(t_token *tkn, t_term *term, int start, int end)
{
	char	*parameter;
	char	*substitution;

	parameter = ft_strsub_mid(tkn->value, start, end);
	if (ft_strequ(parameter, "?"))
		substitution = ft_itoa(term->last_return);
	else
		substitution = get_param_str(parameter, term);
	if (substitution == NULL)
	{
		ft_memdel((void **)&parameter);
		return (-1);
	}
	ft_strcut(tkn->value, start - 2, end + 1);
	tkn->value = ft_strpastei(tkn->value, substitution, start - 2);
	add_quotearray(tkn);
	ft_memdel((void **)&parameter);
	ft_memdel((void **)&substitution);
	return (0);
}

static int	dollar_parameter(t_token *tkn, t_term *term, int start)
{
	int		end;

	end = start;
	while (tkn->value[end])
	{
		if (tkn->value[end] == '}')
			break ;
		end++;
	}
	if (tkn->value[end] != '}')
		return (-1);
	if (substitute_dollar(tkn, term, start, end) == -1)
		return (-1);
	return (1);
}

int	dollar_expansion(t_token *tkn, t_term *term, int dollar)
{
	if (tkn->quotes[dollar] != 0 && tkn->quotes[dollar] != 34)
		return (0);
	else if (tkn->value[dollar + 1] && tkn->value[dollar + 1] == '{')
	{
		tkn->maintoken = tkn_word;
		if (-1 == dollar_parameter(tkn, term, dollar + 2))
			return (-1);
	}
	return (0);
}
