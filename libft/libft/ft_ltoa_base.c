/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 17:57:06 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 16:57:36 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_len_and_allocate(long long n, int base, size_t *n_len)
{
	*n_len = ft_longlonglen_base(n, base);
	return (ft_strnew(*n_len + 1));
}

char	*ft_ltoa_base(long long n, int base)
{
	size_t		n_len;
	size_t		temp;
	char		*str;

	str = get_len_and_allocate(n, base, &n_len);
	if (!str)
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
