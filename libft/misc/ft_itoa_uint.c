/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_uint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 11:19:56 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/06 11:04:01 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_define_uint_length(uintmax_t n, unsigned int base)
{
	int	i;

	i = 0;
	while ((n / base) > 0)
	{
		i++;
		n = n / base;
	}
	i++;
	return (i);
}

char	*ft_itoa_uint(uintmax_t n, unsigned int base)
{
	static char		*str;
	int				w;

	str = malloc(sizeof(char) * (ft_define_uint_length(n, base) + 1));
	if (str)
	{
		w = ft_define_uint_length(n, base) - 1;
		str[w + 1] = ('\0');
		while (n >= base)
		{
			str[w--] = ((n % base) + '0');
			n = n / base;
		}
		str[w] = n + '0';
		return (str);
	}
	return (NULL);
}
