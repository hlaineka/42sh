/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_expansion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 19:27:06 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/11 20:28:13 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"
#include "builtins.h"

/*
** Word expansion tokenization substitutes all found unquoted tilde ~ and dollar
** $ characters.
*/

static int	token_value_expansion(t_token *tkn, t_term *term)
{
	int		i;

	i = 0;
	while (tkn->value && tkn->value[i])
	{
		if (tkn->value[i] == '~' && (-1 == tilde_expansion(tkn, term, i)))
			return (-1);
		if (tkn->value[i] == '$' && (-1 == dollar_expansion(tkn, term, i)))
			return (-1);
		i++;
	}
	return (0);
}

t_token	*word_expansions(t_token *first, t_term *term)
{
	t_token	*temp;
	t_token	*temp_sub;

	temp = first;
	while (temp)
	{
		if (-1 == token_value_expansion(temp, term))
		{
			delete_tokens(first);
			return (NULL);
		}
		temp_sub = temp->subtokens;
		while (temp_sub)
		{
			if (-1 == token_value_expansion(temp_sub, term))
			{
				delete_tokens(first);
				return (NULL);
			}
			temp_sub = temp_sub->next;
		}
		temp = temp->next;
	}
	return (first);
}
