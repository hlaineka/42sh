/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 15:28:30 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/07 09:58:20 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

int		ft_create_padding_str(t_all *all)
{
	if (all->padding_len)
	{
		free(all->padding_str);
		if (!(all->padding_str = ft_strnew(all->padding_len + 1)))
			return (0);
		ft_memset(all->padding_str, all->padding_char, all->padding_len);
	}
	return (1);
}
