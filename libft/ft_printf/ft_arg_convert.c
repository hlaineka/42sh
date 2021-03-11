/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:42:56 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/08/11 15:13:59 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

int			ft_arg_convert(t_all *all)
{
	int		i;

	i = 0;
	while (i < FORMAT_ID_SIZE)
	{
		if (all->format_id & (1 << i))
		{
			all->convert_fun_ptr[i](all);
			return (1);
		}
		i++;
	}
	return (0);
}
