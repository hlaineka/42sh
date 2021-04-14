/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_greatand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:40:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/14 19:33:04 by hlaineka         ###   ########.fr       */
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
	close(new_fd);
	if (job->fd_stdin == -1 || job->fd_stdout == -1 || job->fd_stderr == -1)
	{
		//print fd error
		free_jobs(job);
		return (-1);
	}
	return (0);
}

int	ft_isdigits(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

t_job	*token_greatand(t_job *job, t_term *term, t_node *current)
{
	int		new_fd;
	int		old_fd;
	t_job	*returnable;

	if (!current->right || current->right->left
		|| current->right->right)
		return (NULL);
	returnable = get_job(job, current, term);
	if (!returnable)
		return (NULL);
	if (!current->subtokens)
		old_fd = 1;
	else if (current->subtokens->maintoken == tkn_io_number)
		old_fd = ft_atoi(current->subtokens->value);
	else
	{
		free_jobs(returnable);
		return (NULL);
	}
	if (ft_strequ(current->right->command, "-"))
	{
		if (old_fd == 0)
			close(returnable->fd_stdin);
		else if (old_fd == 1)
			close(returnable->fd_stdout);
		else if (old_fd == 2)
			close(returnable->fd_stderr);
		if (-1 == close(old_fd))
		{
			free_jobs(returnable);
			return (NULL);
		}
	}
	else if (ft_isdigits(current->right->command))
	{
		new_fd = atoi(current->right->command);
		if (-1 == new_fd)
			return(NULL);
		if (-1 == add_fd(returnable, old_fd, new_fd))
			return (NULL);
	}
	return(returnable);
}