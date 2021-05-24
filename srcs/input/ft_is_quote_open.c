/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_open.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:06:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/24 23:33:55 by hhuhtane         ###   ########.fr       */
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

	temp_quote = 0;
	if (quote == PROMPT_START)
		return (PROMPT_NORMAL);
	while (*str)
	{
		check_character(*str, &quote, &temp_quote);
		str++;
	}
	if (temp_quote)
		quote = temp_quote;
	return (quote);
}
