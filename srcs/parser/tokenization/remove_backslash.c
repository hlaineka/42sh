/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_backslash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 14:05:02 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/22 14:18:16 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/*
** functions to remove quotes at the end of tokenization
*/

static int	get_escchar_value(char *str, int *i)
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

static int	handle_quoted_escchar(char *str, int *i)
{
	int	returnable;

	returnable = str[*i];
	*i = *i + 1;
	if (str[*i] == 36 || str[*i] == 96 || str[*i] == 34 || str[*i] == 92)
	{
		returnable = str[*i];
		*i = *i + 1;
	}
	else if (str[*i] == '\n')
	{
		returnable = str[*i + 1];
		*i = *i + 1;
	}
	return (returnable);
}

char	*remove_backslash(char *input)
{
	int		i;
	int		w;
	bool	single_quoted;
	bool	double_quoted;

	i = -1;
	w = 0;
	single_quoted = FALSE;
	double_quoted = FALSE;
	while (input[++i])
	{
		if (input[i] == 34)
			double_quoted = !double_quoted;
		if (input[i] == 39)
			single_quoted = !single_quoted;
		if (input[i] == 92 && double_quoted)
			input[w] = handle_quoted_escchar(input, &i);
		else if (input[i] == 92 && !single_quoted)
			input[w] = get_escchar_value(input, &i);
		else
			input[w] = input[i];
		w++;
	}
	while (w < i)
		input[w++] = '\0';
	return (input);
}