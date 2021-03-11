/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:37:32 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/07 11:38:46 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

void	ft_do_flags(t_all *all)
{
	int		i;

	i = 0;
	while (i < FLAGS_SIZE)
	{
		if ((all->format_info & (1 << i)))
		{
			all->flags_fun_ptr[i](all);
		}
		i++;
	}
}
