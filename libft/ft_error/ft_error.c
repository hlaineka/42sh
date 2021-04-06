/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 12:14:06 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/01 15:28:09 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_error.h"

/*
** functions ment to make manual error handling easier. A string array is
** initialized with all the error messages, and it can be accessed with the
** error number as an index. Added index 40, "Unknown error"
*/

void	ft_perror(const char *program_name, const char *message)
{
	ft_printf_fd(2, "%s: %s", program_name, message);
}

void	ft_error(int status, const char *program_name, const char *format, ...)
{
	va_list	source;

	va_start(source, format);
	if (program_name && program_name[0] != '\0')
		ft_printf_fd(2, "%s: ", program_name);
	ft_printer(format, &source);
	ft_printf_fd(2, "\n");
	if (status)
		ft_exit(status);
}
