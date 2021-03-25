/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base_prefix.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/24 11:47:20 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 17:25:40 by hhuhtane         ###   ########.fr       */
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

static void	*get_len_and_allocate(size_t *n_len, int n, int base)
{
	*n_len = intlen_prefix(n, base);
	return (ft_strnew(*n_len + 1));
}

char	*ft_itoa_base_prefix(int n, int base, char *prefix)
{
	size_t		n_len;
	size_t		temp;
	char		*str;

	if (n < 0)
		prefix[0] = '-';
	str = get_len_and_allocate(&n_len, n, base);
	if (!str)
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
