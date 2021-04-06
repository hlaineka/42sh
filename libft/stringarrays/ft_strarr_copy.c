/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarr_copy.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:54:09 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 13:08:39 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** copies the contents of char **src to freshly (m)allocated strings in an
** (m)allocated array, and returns a pointer to that new array.
** does not free char **src. The char **src should be NULL terminated.
*/

#include "libft.h"

char	**ft_strarr_copy(char **src)
{
	int		i;
	char	**returnable;

	i = 0;
	if (!src)
		return (NULL);
	returnable = malloc(sizeof(char *) * (ft_array_length(src) + 1));
	while (src && src[i])
	{
		returnable[i] = ft_strdup(src[i]);
		i++;
	}
	returnable[i] = NULL;
	return (returnable);
}
