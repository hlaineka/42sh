/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_quote_open.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:06:04 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/25 20:22:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int				ft_is_quote_open(int quote, char *str)
{
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
