/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 12:19:30 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/03/24 12:36:11 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_intlen_base(int n, int base)
{
	size_t		len;

	len = 1;
	if (n < 0)
		len++;
	while (n >= base || n <= -base)
	{
		n = n / base;
		len++;
	}
	return (len);
}
