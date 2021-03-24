/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmaxlen_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 12:19:30 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 13:09:32 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_uintmaxlen_base(uintmax_t n, uintmax_t base)
{
	size_t		len;

	len = 1;
	while (n >= base)
	{
		n = n / base;
		len++;
	}
	return (len);
}
