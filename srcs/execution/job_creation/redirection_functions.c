/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_functions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 13:30:11 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/28 16:08:50 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
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
	return (returnable);
}

int	get_fd(t_node *current, int default_fd)
{
	int	returnable;

	returnable = default_fd;
	if (current->subtokens && current->subtokens->maintoken == tkn_io_number)
		returnable = ft_atoi(current->subtokens->value);
	return (returnable);
}

int	close_fd(int old_fd)
{
	int			returnable;

	if (old_fd == 0)
		returnable = close(STDIN_FILENO);
	else if (old_fd == 1)
		returnable = close(STDOUT_FILENO);
	else if (old_fd == 2)
		returnable = close(STDERR_FILENO);
	else
		returnable = close(old_fd);
	if (returnable == -1)
		ft_printf_fd(STDERR_FILENO, "Bad file descriptor %i", old_fd);
	return (returnable);
}
