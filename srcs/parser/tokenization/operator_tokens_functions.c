/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_tokens_functions.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 11:31:16 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 12:33:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** The index of every character is marked either by 0, or the ascii
** value of the quoting character that applies. If multiple quotes
** apply at any given point, the sum of those ascii values is in quote_values.
*/

void	check_tkn_quotes(t_token *current)
{
	int		*quote_values;
	bool	single_quote;
	bool	double_quote;
	int		i;

	quote_values = (int *)malloc(sizeof(int) * ft_strlen(current->value));
	ft_bzero(quote_values, ft_strlen(current->value));
	double_quote = FALSE;
	single_quote = FALSE;
	i = 0;
	while (current->value[i])
	{
		if (current->value[i] == 34)
			double_quote = !double_quote;
		if (current->value[i] == 44)
			single_quote = !single_quote;
		if (double_quote)
			quote_values[i] = quote_values[i] + 34;
		if (single_quote)
			quote_values[i] = quote_values[i] + 39;
		//add backslash handling here.
		i++;
	}
	current->tokens = quote_values;
}
