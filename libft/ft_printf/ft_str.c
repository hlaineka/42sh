/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 14:47:54 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/07 11:15:07 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

void		convert_str(void *param)
{
	t_all		*all;

	all = (t_all*)param;
	if (!all->arg_str)
	{
		all->convert_str = ft_strdup("(null)");
		all->arg_len = 6;
		if ((all->format_info & (1 << PRECISION_INDEX)) && \
			all->arg_len > all->precision)
			all->arg_len = all->precision;
	}
	else
	{
		all->arg_len = ft_strlen(all->arg_str);
		if ((all->format_info & (1 << PRECISION_INDEX)) && \
			all->arg_len > all->precision)
			all->arg_len = all->precision;
		all->convert_str = ft_strnew(all->arg_len + 1);
		ft_strncat(all->convert_str, all->arg_str, all->arg_len);
	}
}

void		get_str(t_all *all)
{
	all->arg_str = va_arg(all->args, char*);
}
