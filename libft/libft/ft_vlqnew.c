/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlqnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 11:36:49 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/26 14:32:02 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_u64		*ft_vlqnew(t_u32 size)
{
	t_u64	*new;

	if (size == 0)
		return (NULL);
	if (!(new = (t_u64*)malloc(sizeof(t_u64) * size)))
		return (NULL);
	return (new);
}
