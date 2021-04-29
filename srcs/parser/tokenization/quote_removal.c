/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:49:09 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 09:56:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** functions to remove quotes at the end of tokenization
*/

int	get_escchar_value(int c)
{
	if (c == '0')
		return ('\0');
	if (c == 'n')
		return ('\n');
	if (c == 'r')
		return ('\r');
	if (c == 't')
		return ('\t');
	if (c == 'b')
		return ('\b');
	if (c == 'f')
		return ('\f');
	if (c == 'v')
		return ('\v');
	if (c == 'r')
		return ('\r');
	return (c);
}

/*
** ascii 92 == \
*/

char	*replace_escchar(char *str)
{
	int	w;
	int	i;

	w = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == 92)
		{
			i++;
			if (str[i] == '\n')
				i++;
			else
				str[i] = get_escchar_value(str[i]);
		}
		str[w] = str[i];
		w++;
		i++;
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
		ft_remove_chars(temp->value, 39);
		ft_remove_chars(temp->value, 34);
		replace_escchar(temp->value);
		temp = temp->next;
	}
}
