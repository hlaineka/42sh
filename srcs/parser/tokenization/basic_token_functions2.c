/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:54:13 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/25 19:31:22 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** Functions to help with basic tokenization
*/

static int	get_quotevalue(int c, bool *backslash, bool *single_quote,
bool *double_quote)
{
	int	returnable;

	returnable = 0;
	if (c == 34 && *single_quote == FALSE && *backslash == FALSE)
		*double_quote = !*double_quote;
	if (c == 39 && *double_quote == FALSE && *backslash == FALSE)
		*single_quote = !*single_quote;
	if (c == 92 && *single_quote == FALSE)
		*backslash = TRUE;
	if (*double_quote == TRUE)
		returnable = returnable + 34;
	if (*single_quote == TRUE)
		returnable = returnable + 39;
	if (*backslash == TRUE)
		returnable = returnable + 92;
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
		quotearray = init_quotearray(current);
		double_quote = FALSE;
		single_quote = FALSE;
		backslash = FALSE;
		i = 0;
		while (current->value[i])
		{
			quotearray[i] = get_quotevalue(current->value[i], &backslash,
					&single_quote, &double_quote);
			if (i > 0 && current->value[i - 1] == 92 && backslash == TRUE)
				backslash = FALSE;
			i++;
		}
		current->quotes = quotearray;
	}
	return (current);
}

int	*init_quotearray(t_token *current)
{
	int	*quotearray;

	if (current->quotes)
		ft_memdel((void **)&current->quotes);
	quotearray = malloc(sizeof(int) * ft_strlen(current->value) + 1);
	ft_bzero(quotearray, sizeof(int) * ft_strlen(current->value));
	return (quotearray);
}

t_token	*push_to_front(t_token *input, t_token *stack)
{
	input->next = NULL;
	input->prev = stack;
	if (stack)
		stack->next = input;
	return (input);
}

t_token	*push_to_end(t_token *input, t_token *output)
{
	t_token	*returnable;
	t_token	*temp;

	returnable = output;
	temp = output;
	if (!output)
	{
		returnable = input;
		returnable->next = NULL;
		returnable->prev = NULL;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = input;
		input->next = NULL;
		input->prev = temp;
	}
	return (returnable);
}
