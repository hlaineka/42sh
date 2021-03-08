/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 12:10:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 15:30:10 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

void		convert_percent(void *param)
{
	return ((void)param);
}

void		get_percent(t_all *all)
{
	all->convert_str = ft_strdup("%");
	all->arg_len = 1;
}
