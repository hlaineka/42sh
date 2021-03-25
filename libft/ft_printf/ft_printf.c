/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/15 12:44:38 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/24 20:02:01 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static void	lst_delete(void *data, size_t i)
{
	ft_bzero(data, i);
	free(data);
}

static void	ft_write_lst(t_list *lst, size_t *len)
{
	t_list		*ptr;

	ptr = lst;
	*len = 0;
	while (lst)
	{
		*len += write(STDOUT_FILENO, lst->content, lst->content_size);
		lst = lst->next;
	}
	ft_lstdel(&ptr, &lst_delete);
}

static int	ft_lst_to_str(t_list *lst, char **ret, size_t *len)
{
	t_list		*ptr;
	size_t		i;

	ptr = lst;
	*len = 0;
	i = 0;
	while (lst)
	{
		*len += lst->content_size;
		lst = lst->next;
	}
	lst = ptr;
	*ret = ft_strnew(*len + 1);
	if (!(*ret))
		return (0);
	while (lst)
	{
		ft_memmove(*ret + i, lst->content, lst->content_size);
		i += lst->content_size;
		lst = lst->next;
	}
	ft_lstdel(&ptr, &lst_delete);
	return (1);
}

/*
** FT_ASPRINTF ("allocate string & print format to the string") goes through
** the format string and allocates right amount of memory to the string that
** it returns. Otherwise it works as normal printf.
*/

int	ft_asprintf(char **ret, const char *format, ...)
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
	if (!(ft_lst_to_str(all.parsed_args, ret, &len)))
		return (-1);
	return (len);
}

/*
** FT_PRINTF parses the format string and prints the string according to it.
*/

int	ft_printf(const char *format, ...)
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
	ft_write_lst(all.parsed_args, &len);
	return (len);
}
