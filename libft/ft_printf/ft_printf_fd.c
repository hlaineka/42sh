/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 12:44:38 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/13 23:46:57 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static void		ft_write_lst(int fd, t_list *lst, size_t *len)
{
	t_list		*ptr;

	ptr = lst;
	*len = 0;
	while (lst)
	{
		*len += write(fd, lst->content, lst->content_size);
		lst = lst->next;
	}
	ft_lstdel(&ptr, &ft_lstfree);
}

/*
** FT_PRINTF_FD parses the format string and prints the string according to
** fd.
*/

int				ft_printf_fd(int fd, const char *format, ...)
{
	t_all		all;
	size_t		len;

	if (!(ft_initialize(&all, format, &len)))
		return (-1);
	if (*all.format_ptr)
	{
		va_start(all.args, format);
		if (!ft_parse(&all))
			return (-1);
		va_end(all.args);
	}
	ft_write_lst(fd, all.parsed_args, &len);
	return (len);
}
