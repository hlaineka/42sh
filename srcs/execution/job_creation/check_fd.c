/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:11:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/03 11:58:49 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int	check_fd(int fd, int errormessage)
{
	struct stat	*buf;
	int			returnable;

	buf = NULL;
	buf = malloc(sizeof(struct stat));
	returnable = 0;
	if (-1 == fstat(fd, buf))
	{
		if (errormessage == 1)
			ft_printf_fd(STDERR_FILENO, "Bad file descriptor\n");
		ft_free(buf);
		return (-1);
	}
	if (buf->st_mode & S_IRUSR)
		returnable = 3;
	if (buf->st_mode & S_IWUSR)
		returnable++;
	ft_free(buf);
	return (returnable);
}
