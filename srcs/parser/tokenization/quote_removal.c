/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:49:09 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/22 14:15:11 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** removes double quotes if they are not inside single quotes or backslashed
** Removes single quotes unless they are inside double quotes or backslashed
*/

char	*remove_quotes(char *str, int *quotes)
{
	int		i;
	int		w;

	i = -1;
	w = 0;
	while (str[++i])
	{
		if ((str[i] == 34 && quotes[i] != 39 && quotes[i] != 92)
			|| (str[i] == 39 && quotes[i] != 34 && quotes[i] != 92))
			continue ;
		else
			str[w] = str[i];
		w++;
	}
	while (w < i)
		str[w++] = '\0';
	return (str);
}

void	quote_removal(t_token *first)
{
	t_token	*temp;

	temp = first;
	while (temp)
	{
		remove_quotes(temp->value, temp->quotes);
		temp = temp->next;
	}
}
