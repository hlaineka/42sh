/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_to_lst.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 11:15:21 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/07 11:15:44 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_heikki.h"

void		ft_full_str_to_list(t_all *all)
{
	t_list		*txt_list;

	txt_list = ft_lstnew(all->full_str, all->combined_len);
	ft_lstappend(&all->parsed_args, txt_list);
}
