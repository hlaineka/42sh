/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_longlonglen_base.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:04:12 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/07 18:15:31 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_longlonglen_base(long long n, int base)
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
