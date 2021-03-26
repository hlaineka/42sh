/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_open.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:06:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/26 12:30:54 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	ft_is_quote_open(int quote, char *str)
{
	if (quote == PROMPT_START)
		return (PROMPT_NORMAL);
	while (*str)
	{
		if (!quote && ft_strchr("'\"\\`", *str))
			quote = *str;
		else if ((quote == '\\' && *str != '\n') || (quote == *str))
			quote = '\0';
		str++;
	}
	return (quote);
}
