/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:30:11 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/29 13:54:32 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <sys/stat.h>
#include <fcntl.h>

t_job	*get_left_job(t_job *job, t_node *current, t_term *term)
{
	t_job	*returnable;

	returnable = NULL;
	if (!current)
		return (NULL);
	if (current->left)
		returnable = tree_traversal(job, current->left, term);
	if (current->left && !returnable)
		return (NULL);
	if (!returnable && !job)
		returnable = init_job(term);
	else if (!returnable)
		returnable = job;
	return (returnable);
}

t_job	*get_right_job(t_job *job, t_node *current, t_term *term)
{
	t_job	*returnable;

	returnable = NULL;
	if (current->right)
		returnable = tree_traversal(job, current->right, term);
	else
		returnable = job;
	return (returnable);
}

char	*get_filename(t_node *current)
{
	char	*returnable;
	t_token	*temp;

	temp = current->subtokens;
	if (!temp)
		return (NULL);
	while (temp->next && temp->maintoken != tkn_word)
		temp = temp->next;
	if (temp->maintoken != tkn_word)
		return (NULL);
	returnable = temp->value;
	return(returnable);
}

int	add_fd(t_job *job, int old_fd, int new_fd)
{
	t_process	*temp;

	temp = job->first_process;
	while (temp && temp->next)
		temp = temp->next;
	if (old_fd == 0)
		temp->fd_stdin = dup2(new_fd, job->fd_stdin);
	else if (old_fd == 1)
		temp->fd_stdout = dup2(new_fd, job->fd_stdout);
	else if (old_fd == 2)
		temp->fd_stderr = dup2(new_fd, job->fd_stderr);
	else
	{
		//this has to be handled somehow
		//print fd error
		free_jobs(job);
		return (-1);
	}
	close(new_fd);
	if (temp->fd_stdin == -1 || temp->fd_stdout == -1 || temp->fd_stderr == -1)
	{
		//print fd error
		free_jobs(job);
		return (-1);
	}
	return (0);
}

int	get_fd(t_node *current, int default_fd)
{
	int	returnable;

	returnable = default_fd;
	if (current->subtokens && current->subtokens->maintoken == tkn_io_number)
		returnable = ft_atoi(current->subtokens->value);
	return (returnable);
}

int	close_fd(t_job *job, int old_fd)
{
	int			returnable;
	t_process	*temp;

	temp = job->first_process;
	while (temp && temp->next)
		temp = temp->next;
	if (old_fd == 0)
		returnable = close(temp->fd_stdin);
	else if (old_fd == 1)
		returnable = close(temp->fd_stdout);
	else if (old_fd == 2)
		returnable = close(temp->fd_stderr);
	else
		returnable = close(old_fd);
	if (returnable == -1)
	{
		ft_printf_fd(2, "Bad file descriptor %i", old_fd);
		free_jobs(job);
	}
	return (returnable);
}
