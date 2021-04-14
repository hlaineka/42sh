/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_less.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/12 10:52:24 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/13 12:28:35 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>
#include <fcntl.h>

static t_job	*get_job(t_job *job, t_node *current, t_term *term)
{
	t_job	*returnable;

	returnable = NULL;
	if (job)
		returnable = job;
	if (current->left && returnable)
	{
		free_jobs(job);
		return (NULL);
	}
	if (current->left)
		returnable = tree_traversal(current->left, term);
	if (current->left && !returnable)
		return (NULL);
	if (!returnable)
		returnable = init_job();
	return (returnable);
}

static int	add_fd(t_job *job, int old_fd, int new_fd)
{
	if (old_fd == 0)
		job->fd_stdin = dup2(new_fd, job->fd_stdin);
	else if (old_fd == 1)
		job->fd_stdout = dup2(new_fd, job->fd_stdout);
	else if (old_fd == 2)
		job->fd_stderr = dup2(new_fd, job->fd_stderr);
	else
	{
		//print fd error
		free_jobs(job);
		return (-1);
	}
	if (job->fd_stdin == -1 || job->fd_stdout == -1 || job->fd_stderr == -1)
	{
		//print fd error
		free_jobs(job);
		return (-1);
	}
	return (0);
}

static int	open_fd(char *filename, t_term *term)
{
	int	returnable;

	//add filename path checking
	if (term->flag_noclobber == 0)
		returnable = open(filename, O_RDONLY);
	else
		returnable = open(filename, O_RDWR | O_APPEND);
	if (returnable == -1)
		ft_printf("open failed\n"); //
	return (returnable);
}

static char	*get_filename(char	*file)
{
	return(file);
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

	if (!current->right || current->right->left
		|| current->right->right)
		return (NULL);
	returnable = get_job(job, current, term);
	if (!returnable)
		return (NULL);
	if (!current->subtokens)
		old_fd = 0;
	else
		old_fd = ft_atoi(current->subtokens->value);
	filename = get_filename(current->right->command);
	new_fd = open_fd(filename, term);
	if (-1 == new_fd)
		return(NULL);
	if (-1 == add_fd(returnable, old_fd, new_fd))
		return (NULL);
	return(returnable);
}
