/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_chars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 10:50:46 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 12:58:14 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_remove_chars(char *str, int c)
{
	int		i;
	int		w;

	i = -1;
	w = 0;
	while (str[++i])
	{
		if (str[i] == c)
			continue ;
		str[w] = str[i];
		w++;
	}
	while (w < i)
		str[w++] = '\0';
	return (str);
}
