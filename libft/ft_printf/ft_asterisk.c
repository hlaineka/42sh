/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_asterisk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 11:12:45 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/07 13:05:15 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

size_t			ft_precision_asterisk(t_all *all)
{
	int			arg_asterisk;

	arg_asterisk = va_arg(all->args, int);
	all->format_ptr++;
	if (arg_asterisk < 0)
	{
		all->format_info = all->format_info & ~(1 << PRECISION_INDEX);
		return (0);
	}
	return (arg_asterisk);
}

size_t			ft_width_asterisk(t_all *all)
{
	int			arg_asterisk;

	arg_asterisk = va_arg(all->args, int);
	all->format_ptr++;
	if (arg_asterisk >= 0)
		return (arg_asterisk);
	all->format_info = all->format_info | (1 << MINUS_INDEX);
	return (-arg_asterisk);
}
