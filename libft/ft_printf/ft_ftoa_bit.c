/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ftoa_bit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 15:16:55 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/07 15:51:31 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

static long double		round_float(long double f, int prec)
{
	t_ldbits				ldu;
	long double				ld_temp;

	ld_temp = ft_pow(10, prec);
	ldu.ld = f - (uintmax_t)f;
	if (ldu.bits.m == 0 && (uintmax_t)(f * ld_temp) % 2 == 0)
		return (f);
	else
		return (f + (0.5 / ld_temp));
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
		f = f - (unsigned long long)f;
		f *= 10.0;
		num = (unsigned long long)f;
		if (prec == 0)
			f_part[i] = num + '0';
		else
			f_part[i] = (num % 10) + '0';
		i++;
	}
	f_part[i] = '\0';
	return (f_part);
}

static char				*special_cases(t_ldbits ldu, char *sign)
{
	if (ldu.bits.sign & 1)
		*sign = '-';
	if (ldu.bits.exp == 0x7FFF)
	{
		if (ldu.bits.m == 0)
			return (ft_strdup("inf"));
		else
		{
			*sign = '\0';
			return (ft_strdup("nan"));
		}
	}
	return (NULL);
}

char					*ft_lftoa_bit(long double f, size_t prec, char *sign)
{
	t_ldbits				ldu;
	char					*digits_str;
	char					*decimals_str;
	char					*res;

	ldu.ld = f;
	if ((res = special_cases(ldu, sign)))
		return (res);
	if (f < 0)
		f = -f;
	if (prec < 19)
		f = round_float(f, prec);
	digits_str = ft_uintmaxtoa_base((uintmax_t)f, 10);
	if (!(decimals_str = dot_float_str(f, prec)))
		decimals_str = ft_strnew(0);
	res = ft_strjoin(digits_str, decimals_str);
	free(digits_str);
	free(decimals_str);
	return (res);
}
