/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dgreat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 12:25:59 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/02 20:36:47 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include <sys/stat.h>
#include <fcntl.h>

static int	open_fd(char *filename, int old_fd)
{
	int	returnable;

	returnable = 0;
	if (-1 != check_fd(old_fd))
		returnable = close(old_fd);
	if (returnable >= 0)
		returnable = open(filename, O_RDWR | O_APPEND | O_CREAT, S_IRWXU
				| S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	if (returnable == -1)
		ft_printf("open failed\n"); //
	return (returnable);
}

/*
** open(filename, O_RDWR | O_CREAT | O_TRUNC):
** opens the file with read and write permission, creates the file if it
** does not exists and overwrites the data on the file AND truncates all
** excess residual data left from overwrite.
*/

t_job	*token_dgreat(t_job *job, t_term *term, t_node *current)
{
	int		new_fd;
	int		old_fd;
	char	*filename;
	t_job	*returnable;

	old_fd = get_fd(current, 1);
	filename = get_filename(current);
	if (!filename)
		return (NULL);
	new_fd = open_fd(filename, old_fd);
	if (-1 == new_fd)
		return (NULL);
	returnable = get_left_job(job, current, term);
	if (!returnable)
		return (NULL);
	return (returnable);
}
