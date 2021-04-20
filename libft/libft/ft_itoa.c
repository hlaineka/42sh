/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:35:03 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/20 13:18:44 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** turns intiger value to char*
*/

int	ft_define_length(int n)
{
	int	i;
	int	int_min;

	int_min = -2147483647;
	i = 1;
	if (n < int_min)
		return (11);
	if (n < 0)
	{
		i++;
		n = n * (-1);
	}
	while ((n / 10) > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	static char	*str;
	int			w;

	str = (char *)malloc(sizeof(char) * (ft_define_length(n) + 1));
	if (!str)
		return (NULL);
	w = ft_define_length(n) - 1;
	str[w + 1] = ('\0');
	if (n == T_INT_MIN)
	{
		return (ft_strdup("-2147483648"));
	}
	if (n < 0)
	{
		str[0] = ('-');
		n = n * (-1);
	}
	while (n >= 10)
	{
		str[w--] = ((n % 10) + '0');
		n = n / 10;
	}
	str[w] = n + '0';
	return (str);
}
