/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_great.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/08 15:32:34 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/16 11:57:10 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>
#include <fcntl.h>

static int	open_fd(char *filename, t_term *term)
{
	int	returnable;

	//add filename path checking
	if (term->flag_noclobber == 0)
		returnable = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP
				| S_IXGRP | S_IROTH | S_IXOTH);
	else
		returnable = open(filename, O_RDWR | O_APPEND);
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

t_job	*token_great(t_job *job, t_term *term, t_node *current)
{
	int		new_fd;
	int		old_fd;
	char	*filename;
	t_job	*returnable;
	
	old_fd = get_fd(current, 1);
	returnable = get_left_job(job, current, term);
	if (!returnable)
		return (NULL);
	filename = get_filename(current);
	new_fd = open_fd(filename, term);
	if (-1 == new_fd)
		return(NULL);
	if (-1 == add_fd(returnable, old_fd, new_fd))
		return (NULL);
	return(returnable);
}
