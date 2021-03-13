/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:25:54 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/13 23:46:42 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** GET_PLAIN_TXT check if there is '%' or '/' or if not it finds the ending
** null characterin format. It counts the len from start to that char and
** and allocates memory for that amount to the linked list and copies the
** characters.
*/

static int		get_plain_txt(t_all *all)
{
	intmax_t	len;
	char		*end_ptr;
	t_list		*txt_list;

	if (!(end_ptr = ft_strchr(all->format_ptr, '%')) &&
		!(end_ptr = ft_strchr(all->format_ptr, '\\')))
		len = ft_strlen(all->format_ptr);
	else
		len = end_ptr - all->format_ptr;
	if (!(txt_list = ft_lstnew(all->format_ptr, len)))
		return (0);
	ft_lstappend(&all->last_arg, txt_list);
	all->last_arg = all->last_arg->next;
	all->len += len;
	all->format_ptr += len;
	return (1);
}

/*
** FT_PARSE goes through the format_str and collects everything to a
** linked list.
*/

int				ft_parse(t_all *all)
{
	while (all->format_ptr && *all->format_ptr)
	{
		if (!get_plain_txt(all))
			return (0);
		if (!get_variable(all))
			return (1);
	}
	return (1);
}
