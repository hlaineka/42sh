/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:04:53 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/24 15:35:58 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** allocates new string of SIZE and initializes it with \0
*/

char	*ft_strnew(size_t size)
{
	unsigned int	i;
	char			*returnable;

	i = 0;
	returnable = (char *)malloc(sizeof(char) * size + 1);
	if (returnable)
	{
		while (i < size)
		{
			returnable[i] = '\0';
			i++;
		}
		returnable[i] = '\0';
		return (returnable);
	}
	return (NULL);
}
