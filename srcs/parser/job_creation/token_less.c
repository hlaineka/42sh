/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:52:24 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/16 11:57:33 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>
#include <fcntl.h>

static int	open_fd(char *filename)
{
	int	returnable;

	//add filename path checking
	returnable = open(filename, O_RDONLY);
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

t_job	*token_less(t_job *job, t_term *term, t_node *current)
{
	int		new_fd;
	int		old_fd;
	char	*filename;
	t_job	*returnable;

	old_fd = get_fd(current, 0);
	returnable = get_left_job(job, current, term);
	if (!returnable)
		return (NULL);
	filename = get_filename(current);
	new_fd = open_fd(filename);
	if (-1 == new_fd)
		return(NULL);
	if (-1 == add_fd(returnable, old_fd, new_fd))
		return (NULL);
	return(returnable);
}