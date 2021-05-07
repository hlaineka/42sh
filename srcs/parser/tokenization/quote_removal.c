/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_removal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:49:09 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/07 15:24:18 by hlaineka         ###   ########.fr       */
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
** If backslash is inside double quotes, only $ == ascii 36, ` == ascii 96
** " == ascii 34, \ == ascii 92 and newline == ascii 13 have special meaning.
** Those are handled separately, otherwise the backslash is handled as a normal
** character with no special meaning.
*/

int handle_quoted_escchar(char *str, int *i)
{
	int	returnable;

	returnable = str[*i];
	//ft_printf("\nhandle quoted escchar: %i\n", str[*i + 1]);
	*i = *i + 1;
	if (str[*i] == 36 || str[*i] == 96 || str[*i] == 34 || str[*i] == 92)
	{
		returnable = str[*i];
		*i = *i + 1;
	}
	else if (str[*i] == '\n')
	{
		//ft_printf("\nreplacing newline: %c, %c\n", str[*i - 1], str[*i + 1]);
		returnable = str[*i + 1];
		*i = *i + 1;
	}
	return (returnable);
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
		ft_printf(" %c, %i ", str[i], quotes[i]);
		if (str[i] == 34 && quotes[i] != 39 && quotes[i] != 92)
			continue ;
		if (str[i] == 39 && quotes[i] != 34 && quotes[i] != 92)
			continue ;
		if (str[i] == 92 && quotes[i] == 126)
			str[w] = handle_quoted_escchar(str, &i);
		else if (str[i] == 92 && quotes[i] != 39)
		{
			i++;
			if (str[i] != '\n')
				str[w] = get_escchar_value(str[i]);
			else
				str[w] = str[++i];
		}
		else
			str[w] = str[i];
		w++;
	}
	while (w < i)
		str[w++] = '\0';
	ft_printf("\n%s\n", str);
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
