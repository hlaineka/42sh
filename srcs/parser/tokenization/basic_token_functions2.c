/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:54:13 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 10:08:19 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** Functions to help with basic tokenization
*/

t_token	*init_token(void)
{
	t_token	*returnable;

	returnable = (t_token *)malloc(sizeof(t_token));
	ft_bzero(returnable, sizeof(t_token));
	returnable->value = NULL;
	returnable->subtokens = NULL;
	returnable->next = NULL;
	returnable->prev = NULL;
	return (returnable);
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

/*
** The index of every character is marked either by 0, or the ascii
** value of the quoting character that applies. If multiple quotes
** apply at any given point, the sum of those ascii values is in quote_values.
** ascii 35 = " , ascii 39 = ', ascii 92 = \
*/

t_token	*add_quotearray(t_token *current)
{
	int		*quotearray;
	int		i;
	bool	backslash;
	bool	single_quote;
	bool	double_quote;

	if (current)
	{
		if (current->quotes)
			ft_free(current->quotes);
		quotearray = malloc(sizeof(int) * ft_strlen(current->value) + 1);
		ft_bzero(quotearray, sizeof(int) * ft_strlen(current->value));
		double_quote = FALSE;
		single_quote = FALSE;
		backslash = FALSE;
		i = 0;
		while (current->value[i])
		{
			if (current->value[i] == 34)
				double_quote = !double_quote;
			if (current->value[i] == 44)
				single_quote = !single_quote;
			if (current->value[i] == 92)
				backslash = TRUE;
			if (double_quote)
				quotearray[i] = quotearray[i] + 34;
			if (single_quote)
				quotearray[i] = quotearray[i] + 39;
			if (backslash)
				quotearray[i] = quotearray[i] + 92;
			if (current->value[i] != 92 && backslash == TRUE)
				backslash = FALSE;
			i++;
		}
		current->quotes = quotearray;
	}
	return (current);
}

void	check_quotes(char c, bool *single_quoted, bool *double_quoted)
{
	if (c == 34)
		*double_quoted = !*double_quoted;
	if (c == 39)
		*single_quoted = !*single_quoted;
}

void	check_backslash(char *str, char c, bool *backslash)
{
	if (c == 92)
		*backslash = TRUE;
	else if (str && str[0] && str[ft_strlen(str) - 1] != 92)
		*backslash = FALSE;
}
