/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 15:11:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/02 15:36:58 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int	check_fd(int fd)
{
	struct stat	*buf;
	int			returnable;

	buf = NULL;
	buf = malloc(sizeof(struct stat));
	returnable = 0;
	if (-1 == fstat(fd, buf))
		return (-1);
	if (buf->st_mode & S_IRUSR)
		returnable = 3;
	if (buf->st_mode & S_IWUSR)
		returnable++;
	return (0);
}