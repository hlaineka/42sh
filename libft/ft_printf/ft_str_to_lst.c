/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:15:21 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/13 23:47:16 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		ft_full_str_to_list(t_all *all)
{
	t_list		*txt_list;

	txt_list = ft_lstnew(all->full_str, all->combined_len);
	ft_lstappend(&all->parsed_args, txt_list);
}
