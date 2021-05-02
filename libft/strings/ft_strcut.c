/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 11:58:59 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/02 09:17:18 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** removes the part starting from index start and ending at index end from the
** string str. Does not allocate new space for the new string, but instead
** moves the latter part of the string and pads the end of string with '\0's
*/

char	*ft_strcut(char *str, int start, int end)
{
	int		i;
	int		w;
	int		len;

	len = ft_strlen(str);
	i = start;
	w = end;
	while (str[w])
	{
		str[i] = str[w];
		i++;
		w++;
	}
	while (i <= len)
		str[i++] = '\0';
	return (str);
}
