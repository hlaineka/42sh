/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/27 17:25:54 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 20:34:02 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** GET_PLAIN_TXT check if there is '%' or '/' or if not it finds the ending
** null characterin format. It counts the len from start to that char and
** and allocates memory for that amount to the linked list and copies the
** characters.
*/

static size_t	get_text_len(t_all *all)
{
	char		*end_ptr;
	char		*end_ptr_two;

	end_ptr = ft_strchr(all->format_ptr, '%');
	end_ptr_two = ft_strchr(all->format_ptr, '\\');
	if (end_ptr)
		return (end_ptr - all->format_ptr);
	else if (end_ptr_two)
		return (end_ptr - all->format_ptr);
	return (ft_strlen(all->format_ptr));
}

static int	get_plain_txt(t_all *all)
{
	size_t		len;
	t_list		*txt_list;

	len = get_text_len(all);
	txt_list = ft_lstnew(all->format_ptr, len);
	if (!txt_list)
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

int	ft_parse(t_all *all)
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
