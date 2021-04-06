/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_addstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 11:54:01 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 13:09:07 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Adds a new string to string array. When using with  empty strarray, set the
** pointer to NULL
*/

char	**ft_addstr(char **dest, char *src)
{
	int		i;
	int		w;
	char	**returnable;

	i = 0;
	if (dest)
	{
		while (dest[i] != NULL)
			i++;
	}
	returnable = malloc(sizeof(char *) * (i + 1));
	w = 0;
	while (w < i)
	{
		returnable[w] = ft_strdup(dest[w]);
		free(dest[w]);
		w++;
	}
	returnable[w] = ft_strdup(src);
	returnable[w + 1] = NULL;
	free(dest);
	return (returnable);
}
