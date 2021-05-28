/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 21:44:33 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/28 16:06:33 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

/*
** Functions to handle dollar $ expansions. Currently only handles environment
** parameter substitution.
*/

static void	substitute_dollar(t_token *tkn, t_term *term, int start, int end)
{
	char	*parameter;
	char	*substitution;

	parameter = ft_strsub_mid(tkn->value, start, end);
	if (ft_strequ(parameter, "?"))
		substitution = ft_itoa(term->last_return);
	else
		substitution = ft_strdup(ft_getenv(parameter, term->envp));
	ft_strcut(tkn->value, start - 2, end + 1);
	tkn->value = ft_strpastei(tkn->value, substitution, start - 2);
	add_quotearray(tkn);
	ft_free(parameter);
	ft_free(substitution);
}

static int	dollar_parameter(t_token *tkn, t_term *term, int start)
{
	int		end;

	end = start;
	while (tkn->value[end])
	{
		if (tkn->value[end] == '}' && (tkn->quotes[end] == 0
				|| tkn->quotes[end] == 34))
			break ;
		end++;
	}
	if (tkn->value[end] != '}' || (tkn->quotes[end] != 0 && tkn->quotes[end]
			!= 34))
	{
		ft_printf_fd(STDERR_FILENO, "syntax error near token $");
		return (-1);
	}
	substitute_dollar(tkn, term, start, end);
	return (1);
}

int	dollar_expansion(t_token *tkn, t_term *term, int dollar)
{
	if (tkn->quotes[dollar] != 0 && tkn->quotes[dollar] != 34)
		return (0);
	if (tkn->value[dollar + 1] == '{' && (tkn->quotes[dollar + 1] == 0
			|| tkn->quotes[dollar + 1] == 34))
	{	
		if (-1 == dollar_parameter(tkn, term, dollar + 2))
			return (-1);
	}
	else
		return (0);
	return (0);
}
