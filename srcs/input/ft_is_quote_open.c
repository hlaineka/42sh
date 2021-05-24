/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_open.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:06:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/22 16:06:55 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	ft_is_quote_open(int quote, char *str)
{
	int		temp_quote;

	temp_quote = 0;
	if (quote == PROMPT_START)
		return (PROMPT_NORMAL);
	while (*str)
	{
		if (!quote && ft_strchr("'\"\\`", *str))
			quote = *str;
		else if (quote == '"' && *str == '\\')
		{
			temp_quote = '"';
			quote = '\\';
		}
		else if ((quote == '\\' && *str != '\n') || (quote == *str))
			quote = 0;
		if (quote != '\\' && temp_quote)
		{
			quote = temp_quote;
			temp_quote = 0;
		}
		str++;
	}
	return (quote);
}
