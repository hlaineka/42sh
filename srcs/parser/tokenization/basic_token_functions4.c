/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_token_functions4.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:25:15 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/25 20:53:30 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static int	copy_until(char *dest, char *src, int c)
{
	int	i;

	i = 0;
	dest[i] = src[i];
	i++;
	while (src[i] && src[i] != c)
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}

static int	copy_paranthesis(char *dest, char *src, int *i, int c)
{
	int	w;

	w = 0;
	while (src[*i])
	{
		dest[w++] = src[*i];
		*i = *i + 1;
		if (src[*i] == 123)
			*i = *i + copy_paranthesis(&(dest[w]), src, i, 125);
		if (src[*i] == c)
			break ;
	}
	if (src[*i])
	{
		dest[w++] = src[*i];
		*i = *i + 1;
	}
	else
	{
		ft_printf_fd(2, "Wrong amount of braces/paranthesis\n");
		return (-1);
	}
	return (0);
}

static void	copy_backslash(char *returnable, char **source, int *i, int *w)
{
	returnable[*w] = source[0][*i];
	*i = *i + 1;
	*w = *w + 1;
	returnable[*w] = source[0][*i];
	*i = *i + 1;
	*w = *w + 1;
}

/*
** 92 == \
** 34 == "
** 39 == '
** 123 == {
** 125 == }
** 40 == (
** 41 == )
** 96 == `
*/

int	check_quotes(char **source, int *i, char *returnable, int *maintoken)
{
	int	w;

	w = ft_strlen(returnable);
	if (source[0][*i] == 92)
		copy_backslash(returnable, source, &w, i);
	else if (source[0][*i] == 34)
		*i = *i + copy_until(&returnable[w], &(source[0][*i]), 34);
	else if (source[0][*i] == 39)
		*i = *i + copy_until(&returnable[w], &(source[0][*i]), 39);
	else if (source[0][*i] == 96)
		*i = *i + copy_until(&returnable[w], &(source[0][*i]), 96);
	else if (source[0][*i] == 123)
	{
		if (-1 == copy_paranthesis(&returnable[w], *source, i, 125))
			return (-1);
		*maintoken = tkn_lbrace;
	}
	else if (source[0][*i] == 125)
	{
		ft_printf_fd(2, "Wrong amount of braces/paranthesis\n");
		return (-1);
	}
	return (1);
}
