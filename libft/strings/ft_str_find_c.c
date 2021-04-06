/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_find_c.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 10:27:33 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 13:00:23 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** returns the index of the first occurance of c in src
*/

int	ft_str_find_c(const char *src, int c)
{
	int		i;

	i = 0;
	if (src)
	{
		while (src[i] != '\0')
		{
			if (src[i] == c)
				return (i);
			i++;
		}
		if (src[i] == c)
			return (i);
	}
	return (-1);
}
