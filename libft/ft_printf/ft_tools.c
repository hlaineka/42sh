/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 14:05:56 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/07 11:16:28 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

int			ft_variable_len(t_all *all)
{
	all->combined_len = all->arg_len + all->prefix_len;
	if (all->combined_len < all->width)
	{
		all->padding_len = all->width - all->combined_len;
		all->combined_len = all->width;
	}
	return (all->combined_len);
}

int			get_first_decimal(long double f)
{
	unsigned long long		num;

	num = f;
	f = f - num;
	f = f * 10;
	return (f);
}

long double	get_decimal_remain(long double f)
{
	return (f - (unsigned long long)f);
}

void		future_feature(void *param)
{
	t_all					*all;

	all = (t_all*)param;
	all->convert_str = ft_strdup("This is a possible future feature!");
	all->arg_len = ft_strlen(all->convert_str);
}
