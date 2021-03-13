/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 18:10:53 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/13 23:45:55 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			combine_elements(t_all *all)
{
	char		*mem_ptr;

	if (!(mem_ptr = ft_strnew(all->combined_len + 1)))
		return ;
	all->full_str = mem_ptr;
	if ((all->format_info >> MINUS_INDEX) & 1)
	{
		ft_memcpy(mem_ptr, all->prefix, all->prefix_len);
		mem_ptr += all->prefix_len;
		ft_memcpy(mem_ptr, all->convert_str, all->arg_len);
		mem_ptr += all->arg_len;
		ft_memcpy(mem_ptr, all->padding_str, all->padding_len);
	}
	else if ((all->format_info >> ZERO_INDEX) & 1)
	{
		ft_strcat(all->full_str, all->prefix);
		ft_strcat(all->full_str, all->padding_str);
		ft_strncat(all->full_str, all->convert_str, all->arg_len);
	}
	else
	{
		ft_strcat(all->full_str, all->padding_str);
		ft_strcat(all->full_str, all->prefix);
		ft_strncat(all->full_str, all->convert_str, all->arg_len);
	}
}

void			convert_ouxx(void *param)
{
	t_all		*all;

	all = (t_all*)param;
	all->convert_str = ft_uintmaxtoa_base(all->arg_uint, all->arg_base);
	if ((all->format_id >> UPX_INDEX) & 1)
		ft_strtoupper(all->convert_str);
	all->arg_len = ft_strlen(all->convert_str);
}

void			convert_di(void *param)
{
	t_all		*all;
	char		*str;

	all = (t_all*)param;
	if (((all->format_info >> L_INDEX) & 1) || \
		(all->format_info >> LL_INDEX) & 1)
		str = ft_ltoa_base_prefix(all->arg_int, all->arg_base, all->prefix);
	else
		str = ft_itoa_base_prefix(all->arg_int, all->arg_base, all->prefix);
	all->convert_str = str;
	all->prefix_len = ft_strlen(all->prefix);
	all->arg_len = ft_strlen(str);
}

void			convert_double(void *param)
{
	t_all		*all;
	char		*str;

	all = (t_all*)param;
	if (!((all->format_info >> PRECISION_INDEX) & 1))
		all->convert_str = ft_lftoa_bit(all->arg_double, 6, all->prefix);
	else
	{
		str = ft_lftoa_bit(all->arg_double, all->precision, all->prefix);
		if (!(all->precision) && all->format_info & (1 << HASH_INDEX))
		{
			all->convert_str = ft_strjoin(str, ".");
			free(str);
		}
		else
			all->convert_str = str;
	}
	all->prefix_len = ft_strlen(all->prefix);
	all->arg_len = ft_strlen(all->convert_str);
}
