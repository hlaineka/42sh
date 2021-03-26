/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_variable.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 20:53:19 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 19:54:28 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_printf.h>

static void	get_di(t_all *all)
{
	if ((all->format_info >> H_INDEX) & 1)
		all->arg_int = (short)va_arg(all->args, int);
	else if ((all->format_info >> HH_INDEX) & 1)
		all->arg_int = (signed char)va_arg(all->args, int);
	else if ((all->format_info >> L_INDEX) & 1)
		all->arg_int = (long)va_arg(all->args, long);
	else if ((all->format_info >> LL_INDEX) & 1)
		all->arg_int = (long long)va_arg(all->args, long long);
	else
		all->arg_int = va_arg(all->args, int);
	all->arg_base = 10;
}

static void	get_ouxx(t_all *all)
{
	if ((all->format_info & (1 << H_INDEX)))
		all->arg_uint = (unsigned short)va_arg(all->args, unsigned int);
	else if ((all->format_info & (1 << HH_INDEX)))
		all->arg_uint = (unsigned char)va_arg(all->args, unsigned int);
	else if ((all->format_info & (1 << L_INDEX)))
		all->arg_uint = (unsigned long)va_arg(all->args, unsigned long);
	else if ((all->format_info & (1 << LL_INDEX)))
		all->arg_uint = va_arg(all->args, unsigned long long);
	else
		all->arg_uint = va_arg(all->args, unsigned int);
	if ((all->format_id & (1 << O_INDEX)))
		all->arg_base = 8;
	else if ((all->format_id & (1 << U_INDEX)))
		all->arg_base = 10;
	else
		all->arg_base = 16;
}

void	get_double(t_all *all)
{
	if ((all->format_info >> UPL_INDEX) & 1)
		all->arg_double = va_arg(all->args, long double);
	else if ((all->format_id >> E_INDEX) & 3)
		all->arg_double = va_arg(all->args, long double);
	else
		all->arg_double = (long double)va_arg(all->args, double);
}

static int	ft_collect_var(t_all *all)
{
	if ((all->format_id & DI_MASK))
		get_di(all);
	else if ((all->format_id & OUXX_MASK))
		get_ouxx(all);
	else if ((all->format_id & AAEEFFGG_MASK))
		get_double(all);
	else if ((all->format_id >> PERCENT_INDEX) & 1)
		get_percent(all);
	else if ((all->format_id >> UPC_INDEX) & 3)
		get_char(all);
	else if ((all->format_id >> S_INDEX) & 1)
		get_str(all);
	else if ((all->format_id >> P_INDEX) & 1)
		get_ptr(all);
	return (1);
}

int	get_variable(t_all *all)
{
	if (*all->format_ptr != '%')
		return (1);
	if (!(get_variable_info(all)))
		return (0);
	ft_collect_var(all);
	ft_do_flags(all);
	ft_arg_convert(all);
	ft_precision(all);
	ft_variable_len(all);
	ft_create_padding_str(all);
	combine_elements(all);
	ft_full_str_to_list(all);
	free(all->padding_str);
	free(all->convert_str);
	free(all->full_str);
	return (1);
}
