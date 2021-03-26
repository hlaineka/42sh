/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 12:35:03 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/24 17:15:51 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** turns intiger value to char*
*/

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
