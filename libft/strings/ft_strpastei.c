/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpastei.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 19:22:30 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/02 09:17:11 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates and returns a fresh string, where sting new is replacing the
** character in position i of the dest str.
*/

char	*ft_strpastei(char *dest, char *new, int i)
{
	char	*returnable;
	int		w;
	int		o;

	returnable = ft_strnew(ft_strlen(dest) + ft_strlen(new) + 1);
	w = 0;
	while (w <= i && dest && dest[w])
	{
		returnable[w] = dest[w];
		w++;
	}
	o = 0;
	while (new && new[o])
		returnable[w++] = new[o++];
	while (dest && dest[i])
		returnable[w++] = dest[i++];
	returnable[w] = '\0';
	ft_free(dest);
	return (returnable);
}
