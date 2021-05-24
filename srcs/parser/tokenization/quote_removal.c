/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:49:09 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/24 19:15:11 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "libft.h"

/*
** functions to remove quotes at the end of tokenization
*/

int	get_escchar_value(char *str, int *i)
{
	*i = *i + 1;
	if (str[*i] == '\n')
		*i = *i + 1;
	else if (str[*i] == '0')
		return ('\0');
	else if (str[*i] == 'n')
		return ('\n');
	else if (str[*i] == 'r')
		return ('\r');
	else if (str[*i] == 't')
		return ('\t');
	else if (str[*i] == 'b')
		return ('\b');
	else if (str[*i] == 'f')
		return ('\f');
	else if (str[*i] == 'v')
		return ('\v');
	else if (str[*i] == 'r')
		return ('\r');
	return (str[*i]);
}

/*
** If backslash is inside double quotes, only $ == ascii 36, ` == ascii 96
** " == ascii 34, \ == ascii 92 and newline == ascii 13 have special meaning.
** Those are handled separately, otherwise the backslash is handled as a normal
** character with no special meaning.
*/

void	handle_quoted_escchar(char *str, int *i, int *w)
{
	*i = *i + 1;
	if (str[*i] == 36 || str[*i] == 96 || str[*i] == 34 || str[*i] == 92)
		str[*w] = str[*i];
	else if (str[*i] == '\n')
		*w = *w - 1;
	else
	{
		str[*w] = str[*i - 1];
		*w = *w + 1;
		str[*w] = str[*i];
	}
}

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
		if (str[i] == 92 && quotes[i] == 126)
			handle_quoted_escchar(str, &i, &w);
		else if (str[i] == 92 && quotes[i] != 39)
			str[w] = get_escchar_value(str, &i);
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
