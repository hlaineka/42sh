/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uintmaxtoa_base.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 11:47:20 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/08 10:43:39 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_uintmaxtoa_base(uintmax_t n, uintmax_t base)
{
	size_t		n_len;
	size_t		temp;
	char		*str;

	n_len = ft_uintmaxlen_base(n, base);
	if (!(str = ft_memalloc(sizeof(char) * (n_len + 1))))
		return (NULL);
	str[n_len--] = '\0';
	while (n >= base)
	{
		temp = ft_abs(n % base);
		if (temp < 10)
			str[n_len--] = temp + '0';
		else
			str[n_len--] = temp - 10 + 'a';
		n = n / base;
	}
	temp = ft_abs(n);
	if (temp < 10)
		str[n_len] = temp + '0';
	else
		str[n_len] = temp - 10 + 'a';
	return (str);
}
