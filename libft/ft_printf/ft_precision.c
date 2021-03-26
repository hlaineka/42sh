/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_precision.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:43:54 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 20:02:51 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_precision_helper(t_all *all)
{
	char	*temp;

	temp = ft_strnew(all->precision + all->prefix_len + 1);
	if (!temp)
		return ;
	if (all->prefix[0] == '0' && !(all->prefix[1]))
		all->prefix_len = 0;
	else
		ft_strcpy(temp, all->prefix);
	all->prefix[0] = '\0';
	ft_memset((temp + all->prefix_len), '0', all->precision - all->arg_len);
	ft_strcat(temp, all->convert_str);
	free(all->convert_str);
	all->convert_str = temp;
	all->arg_len = all->precision + all->prefix_len;
	all->prefix_len = 0;
}

void	ft_precision(t_all *all)
{
	if (!(all->format_info & (1 << PRECISION_INDEX)) || \
		!(all->format_id & DIOUXX_MASK))
		return ;
	if (all->precision == 0 && (all->arg_uint == 0 || all->arg_int == 0))
	{
		free(all->convert_str);
		all->convert_str = ft_strnew(0);
		all->arg_len = 0;
	}
	else if (all->precision > all->arg_len)
		ft_precision_helper(all);
}
