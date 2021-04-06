/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_toupper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/02 11:26:14 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 13:01:07 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Turns the str given as a parameter to uppercase.
*/

char	*ft_str_toupper(char *str)
{
	int		i;
	char	*returnable;

	i = 0;
	returnable = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (returnable)
	{
		while (str[i])
		{
			returnable[i] = ft_toupper(str[i]);
			i++;
		}
		returnable[i] = '\0';
	}
	return (returnable);
}
