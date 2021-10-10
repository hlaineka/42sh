/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup_escape.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:34:18 by hlaineka          #+#    #+#             */
/*   Updated: 2021/10/10 10:10:23 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** creates a new string and copies the content of s to it.Returns the new str
*/

char	*ft_strdup_escape(const char *s)
{
	int		i;
	char	*returnable;
	int		length;

	length = ft_strlen(s);
	returnable = NULL;
	returnable = (char *)malloc(sizeof(char) * (length * 2) + 1);
	if (!returnable)
		return (NULL);
	i = 0;
	while (s && s[i] != '\0')
	{
		returnable[i++] = '\\';
		returnable[i] = *s;
		s++;
		i++;
	}
	returnable[i] = '\0';
	return (returnable);
}
