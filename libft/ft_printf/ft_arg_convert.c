/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg_convert.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 17:42:56 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/13 23:45:59 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
