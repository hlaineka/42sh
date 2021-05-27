/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_open.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:06:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/27 13:42:54 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	check_character(char c, int *quote, int *temp_quote)
{
	if (!(*quote) && ft_strchr("'\"\\`", c))
		*quote = c;
	else if (*quote == '"' && c == '\\')
	{
		*temp_quote = '"';
		*quote = '\\';
	}
	else if (*quote == '\\' || *quote == c)
	{
		*quote = *temp_quote;
		*temp_quote = 0;
	}
}

int	ft_is_quote_open(int quote, char *str)
{
	int		temp_quote;
	int		nl;
	int		i;

	i = 0;
	nl = ft_strlen(str) - 1;
	str[nl] = '\0';
	temp_quote = 0;
	if (quote == PROMPT_START)
		return (PROMPT_NORMAL);
	while (str[i])
	{
		check_character(str[i], &quote, &temp_quote);
		i++;
	}
	if (temp_quote)
		quote = temp_quote;
	str[nl] = '\n';
	return (quote);
}
