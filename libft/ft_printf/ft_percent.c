/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_percent.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 12:10:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/13 23:46:48 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		convert_percent(void *param)
{
	return ((void)param);
}

void		get_percent(t_all *all)
{
	all->convert_str = ft_strdup("%");
	all->arg_len = 1;
}
