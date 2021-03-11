/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strarrlen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 14:50:11 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/01/11 10:53:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strarrlen(char **array)
{
	size_t		arrsize;

	arrsize = 0;
	if (!array)
		return (0);
	while (*array)
	{
		arrsize++;
		array++;
	}
	return (arrsize);
}
