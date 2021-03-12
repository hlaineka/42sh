/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:34:02 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/12 16:43:34 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** The ft_strrcat() does the same as ft_strcat, but it append a copy of the
** null-terminated string s2 REVERSED to the end of the null-terminated string
** s1, then add a terminating `\0'.  The string s1 must have sufficient space
** to hold the result.
*/

char	*ft_strrcat(char *s1, const char *s2)
{
	int		i1;
	int		i2;

	i1 = ft_strlen(s1);
	i2 = ft_strlen(s2);
	while(--i2 >= 0)
		s1[i1++] = s2[i2];
	s1[i1] = '\0';
	return (s1);
}
