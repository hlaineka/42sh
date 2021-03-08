/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:57:06 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 10:35:05 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_ltoa_base(long long n, int base)
{
	size_t		n_len;
	size_t		temp;
	char		*str;

	n_len = ft_longlonglen_base(n, base);
	if (!(str = ft_strnew(n_len + 1)))
		return (NULL);
	str[n_len--] = '\0';
	if (n < 0)
		str[0] = '-';
	while (n >= base || n <= -base)
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
