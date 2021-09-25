/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 17:58:27 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/25 19:31:33 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** More functions to help with basic tokenization.
*/

/*
** returns 0 when the current tokenstr should be delimited.
*/

int	handle_operator_token(char *str, char *source, int *i, int *maintoken)
{
	if (ft_strchr(BRACKETS, source[*i]))
		return (0);
	else if (ft_strchr(REDIROPS, source[*i]))
	{
		if (*maintoken != tkn_redirop && !ft_is_nbrstr(str))
			return (0);
		else
			*maintoken = tkn_redirop;
	}
	else if ((*maintoken != tkn_operator || *maintoken != tkn_redirop)
		&& str[0])
		return (0);
	else
		*maintoken = tkn_operator;
	str[ft_strlen(str)] = source[*i];
	return (1);
}

int	handle_word_token(char *str, char *source, int *i, int *maintoken)
{
	int	w;

	if (*maintoken != tkn_word && *maintoken != tkn_lbrace
		&& *maintoken != tkn_lpar)
		return (0);
	w = ft_strlen(str);
	str[w] = source[*i];
	return (1);
}

t_token	*add_subtoken(t_token *current, t_token *sub)
{
	t_token	*returnable;
	t_token	*temp;

	if (!current || !sub)
		return (NULL);
	if (sub->prev)
		sub->prev->next = sub->next;
	if (sub->next)
		sub->next->prev = sub->prev;
	sub->next = NULL;
	returnable = current;
	temp = current->subtokens;
	if (temp)
	{
		while (temp->next)
			temp = temp->next;
		temp->next = sub;
		sub->prev = temp;
	}
	else
	{
		returnable->subtokens = sub;
		sub->prev = returnable;
	}
	return (returnable);
}

t_token	*init_token(void)
{
	t_token	*returnable;

	returnable = (t_token *)malloc(sizeof(t_token));
	ft_bzero(returnable, sizeof(t_token));
	returnable->full_command = NULL;
	returnable->value = NULL;
	returnable->subtokens = NULL;
	returnable->next = NULL;
	returnable->prev = NULL;
	return (returnable);
}
