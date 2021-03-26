/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:28:30 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 20:09:40 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_create_padding_str(t_all *all)
{
	if (all->padding_len)
	{
		free(all->padding_str);
		all->padding_str = ft_strnew(all->padding_len + 1);
		if (!all->padding_str)
			return (0);
		ft_memset(all->padding_str, all->padding_char, all->padding_len);
	}
	return (1);
}
