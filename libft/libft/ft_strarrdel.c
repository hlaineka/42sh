/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 12:28:27 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/09 19:39:16 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strarrdel(char ***arr)
{
	char	**ptr;

	if (!arr)
		return (NULL);
	ptr = *arr;
	while (*ptr)
	{
		ft_strdel(ptr);
		ptr++;
	}
	free(**arr);
	**arr = NULL;
	free(*arr);
	*arr = NULL;
	return (NULL);
}
