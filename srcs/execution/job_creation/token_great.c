/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:32:34 by hlaineka          #+#    #+#             */
/*   Updated: 2021/06/13 11:35:19 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include <sys/stat.h>
#include <fcntl.h>

static int	open_fd(char *filename, t_term *term, int old_fd)
{
	int	returnable;

	returnable = check_fd(old_fd, 0);
	if (-1 != returnable || old_fd < 3)
	{
		if (-1 != returnable)
			returnable = close_fd(old_fd);
		if (returnable >= 0)
		{
			if (term->intern_variables->flag_noclobber == 0)
				returnable = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
						S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
			else
				returnable = open(filename, O_RDWR | O_APPEND);
		}
	}
	return (returnable);
}

/*
** open(filename, O_RDWR | O_CREAT | O_TRUNC):
** opens the file with read and write permission, creates the file if it
** does not exists and overwrites the data on the file AND truncates all
** excess residual data left from overwrite.
*/

t_job	*token_great(t_job *job, t_term *term, t_node *current)
{
	int		old_fd;
	char	*filename;
	t_job	*returnable;

	old_fd = get_fd(current, 1);
	filename = get_filename(current);
	if (!filename)
		return (NULL);
	open_fd(filename, term, old_fd);
	returnable = get_left_job(job, current, term);
	if (!returnable)
		return (NULL);
	return (returnable);
}
