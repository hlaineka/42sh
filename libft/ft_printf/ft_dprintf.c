/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 12:44:38 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 20:16:29 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static void	lst_delete(void *data, size_t i)
{
	ft_bzero(data, i);
	free(data);
}

static void	ft_write_lst(t_list *lst, size_t *len, int fd)
{
	t_list		*ptr;

	ptr = lst;
	*len = 0;
	while (lst)
	{
		*len += write(fd, lst->content, lst->content_size);
		lst = lst->next;
	}
	ft_lstdel(&ptr, &lst_delete);
}

/*
** FT_DPRINTF parses the format string and write output to the given file
** descriptor.
*/

int	ft_dprintf(int fd, const char *format, ...)
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
	ft_write_lst(all.parsed_args, &len, fd);
	return (len);
}
