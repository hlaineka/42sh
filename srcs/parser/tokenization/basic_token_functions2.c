/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 14:54:13 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/07 15:14:41 by hlaineka         ###   ########.fr       */
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
			quotearray[i] = get_quotevalue(current->value[i], &backslash,
					&single_quote, &double_quote);
			if (i > 0 && current->value[i - 1] == 92 && backslash == TRUE)
				backslash = FALSE;
			ft_printf(" %c,%i ", current->value[i], quotearray[i]);
			i++;
		}
		ft_printf("\n");
		current->quotes = quotearray;
	}
	return (current);
}

void	check_quotes(char c, bool *single_quoted, bool *double_quoted)
{
	if (c == 34 && !*single_quoted)
		*double_quoted = !*double_quoted;
	if (c == 39 && ! *double_quoted)
		*single_quoted = !*single_quoted;
}

void	check_backslash(char *str, char c, bool *backslash, bool single_quoted)
{
	if (c == 92 && !single_quoted)
		*backslash = TRUE;
	else if (*backslash == TRUE && str && str[0] && str[ft_strlen(str) - 2] == 92)
		*backslash = FALSE;
}
