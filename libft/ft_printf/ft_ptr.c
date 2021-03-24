/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 09:14:21 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 20:00:14 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ptr_null_with_precision(size_t i, t_all *all)
{
	all->convert_str = ft_strnew(all->precision + 1);
	while (i < all->precision)
		all->convert_str[i++] = '0';
	all->convert_str[i] = '\0';
}

static void	fill_str_with_zeros(size_t i, int zeros, t_all *all)
{
	char			*temp;
	char			*temp2;

	temp = ft_strnew(zeros);
	while ((int)i < zeros)
		temp[i++] = '0';
	temp[i] = '\0';
	temp2 = ft_strjoin(temp, all->convert_str);
	free(all->convert_str);
	free(temp);
	all->convert_str = temp2;
}

void	convert_ptr(void *param)
{
	t_all			*all;
	size_t			i;
	int				zeros;

	i = 0;
	zeros = 0;
	all = (t_all *)param;
	if ((all->format_info & (1 << PRECISION_INDEX)) && all->arg_ptr == NULL)
		ptr_null_with_precision(i, all);
	else
		all->convert_str = ft_uintmaxtoa_base((unsigned long)all->arg_ptr, 16);
	zeros = all->precision - ft_strlen(all->convert_str);
	if (zeros > 0)
		fill_str_with_zeros(i, zeros, all);
	ft_strcpy(all->prefix, "0x");
	all->prefix_len = 2;
	all->arg_len = ft_strlen(all->convert_str);
}

void	get_ptr(t_all *all)
{
	all->arg_ptr = va_arg(all->args, void *);
}
