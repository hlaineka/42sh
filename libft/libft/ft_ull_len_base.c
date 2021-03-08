/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ull_len_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 17:24:36 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/06 13:54:29 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_ull_len_base(unsigned long long n, int base)
{
	size_t		len;
	t_ul64		bbase;

	len = 1;
	bbase = base;
	while (n >= bbase)
	{
		n /= bbase;
		len++;
	}
	return (len);
}
