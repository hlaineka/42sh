/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 11:36:49 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 13:06:22 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_u64	*ft_vlqnew(t_u32 size)
{
	t_u64	*new;

	if (size == 0)
		return (NULL);
	new = (t_u64 *)malloc(sizeof(t_u64) * size);
	if (!new)
		return (NULL);
	return (new);
}
