/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_prefix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 11:47:20 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/10 12:45:41 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	intlen_prefix(int n, int base)
{
	size_t		len;

	len = 1;
	while (n >= base || n <= -base)
	{
		n = n / base;
		len++;
	}
	return (len);
}

char			*ft_itoa_base_prefix(int n, int base, char *prefix)
{
	size_t		n_len;
	size_t		temp;
	char		*str;

	n_len = intlen_prefix(n, base);
	if (n < 0)
		prefix[0] = '-';
	if (!(str = ft_memalloc(sizeof(char) * (n_len + 1))))
		return (NULL);
	str[n_len--] = '\0';
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
