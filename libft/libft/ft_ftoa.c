/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 15:16:55 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/14 15:12:07 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static long double		round_float(long double f, int prec)
{
	long double				round;

	round = 0.5;
	while (prec-- > 0)
		round /= 10.0;
	if (f > 0)
		return (f + round);
	else
		return (f - round);
}

static char				*dot_float_str(long double f, int prec)
{
	unsigned long long		num;
	char					*f_part;
	size_t					i;

	i = 1;
	if (prec < 1 || !(f_part = ft_strnew(prec + 2)))
		return (NULL);
	f_part[0] = '.';
	while (prec-- > 0)
	{
		f *= 10.0;
		num = f;
		f -= num;
		f_part[i] = (num % 10) + '0';
		i++;
	}
	f_part[i] = '\0';
	return (f_part);
}

char					*ft_ftoa(long double f, size_t prec)
{
	char					*i_part;
	char					*f_part;
	char					*res;

	f = round_float(f, prec);
	i_part = ft_ltoa_base((long long)f, 10);
	f_part = dot_float_str(f, prec);
	res = ft_strjoin(i_part, f_part);
	free(i_part);
	free(f_part);
	return (res);
}
