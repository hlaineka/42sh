/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 12:23:25 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/24 13:16:37 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Allocates and returns a "fresh" substring from the string given as argument.
** The substring begins at index START and is of size LEN. If START and LEN
** aren't refering to a valid substring, the behavior is undefined. If the
** allocation fails, the function return NULL
*/

char	*ft_strsub(const char *s, unsigned int start, size_t len)
{
	char			*returnable;
	unsigned int	i;

	i = 0;
	returnable = (char *)malloc(sizeof(char) * (len + 1));
	if (s && returnable)
	{
		while (i < len)
		{
			returnable[i] = s[start + i];
			i++;
		}
		returnable[i] = '\0';
		return (returnable);
	}
	return (NULL);
}
