/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 13:16:47 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/01 07:43:37 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

void	ft_init_flags_ptr(t_all *all)
{
	all->flags_fun_ptr[0] = &ft_flag_hash;
	all->flags_fun_ptr[1] = &ft_flag_zero;
	all->flags_fun_ptr[2] = &ft_flag_minus;
	all->flags_fun_ptr[3] = &ft_flag_space;
	all->flags_fun_ptr[4] = &ft_flag_plus;
}

void	ft_init_fun_ptr(t_all *all)
{
	all->convert_fun_ptr[D_INDEX] = &convert_di;
	all->convert_fun_ptr[I_INDEX] = &convert_di;
	all->convert_fun_ptr[O_INDEX] = &convert_ouxx;
	all->convert_fun_ptr[U_INDEX] = &convert_ouxx;
	all->convert_fun_ptr[X_INDEX] = &convert_ouxx;
	all->convert_fun_ptr[UPX_INDEX] = &convert_ouxx;
	all->convert_fun_ptr[E_INDEX] = &convert_double;
	all->convert_fun_ptr[UPE_INDEX] = &convert_double;
	all->convert_fun_ptr[F_INDEX] = &convert_double;
	all->convert_fun_ptr[UPF_INDEX] = &convert_double;
	all->convert_fun_ptr[G_INDEX] = &future_feature;
	all->convert_fun_ptr[UPG_INDEX] = &future_feature;
	all->convert_fun_ptr[A_INDEX] = &future_feature;
	all->convert_fun_ptr[UPA_INDEX] = &future_feature;
	all->convert_fun_ptr[UPC_INDEX] = &convert_char;
	all->convert_fun_ptr[C_INDEX] = &convert_char;
	all->convert_fun_ptr[UPS_INDEX] = &convert_str;
	all->convert_fun_ptr[S_INDEX] = &convert_str;
	all->convert_fun_ptr[P_INDEX] = &convert_ptr;
	all->convert_fun_ptr[N_INDEX] = &future_feature;
	all->convert_fun_ptr[B_INDEX] = &future_feature;
	all->convert_fun_ptr[PERCENT_INDEX] = &convert_percent;
}

/*
** FT_INITIALIZE initializes all the start values and function
** pointers.
*/

int		ft_initialize(t_all *all, const char *format, size_t *len)
{
	all->format_ptr = (char*)format;
	all->len = len;
	*all->len = 0;
	if (!(all->parsed_args = ft_lstnew(NULL, 0)))
		return (0);
	all->last_arg = all->parsed_args;
	ft_strncpy(all->flags_str, FLAGS, FLAGS_SIZE + 1);
	ft_strncpy(all->l_modifier_str, L_MODIFIER, L_MOD_SIZE + 1);
	ft_strncpy(all->format_id_str, FORMAT_ID, FORMAT_ID_SIZE + 1);
	ft_init_fun_ptr(all);
	ft_init_flags_ptr(all);
	return (1);
}
