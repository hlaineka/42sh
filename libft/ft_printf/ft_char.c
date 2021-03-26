/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/09 12:23:17 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 20:19:51 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	convert_char(void *param)
{
	t_all	*all;

	all = (t_all *)param;
	all->convert_str = ft_strnew(2);
	all->convert_str[0] = all->arg_int;
	all->convert_str[1] = '\0';
	all->arg_len = 1;
}

void	get_char(t_all *all)
{
	all->arg_int = va_arg(all->args, int);
}
