/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_greatand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:40:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/30 14:59:49 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include <sys/stat.h>
#include <fcntl.h>

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

int	dup_fd(t_job *job, int old_fd, int new_fd)
{
	int	returnable;

	returnable = close_fd(job, old_fd);
	if (returnable != -1)
	{
		if (old_fd == 0)
			job->fd_stdin = dup(new_fd);
		else if (old_fd == 1)
			job->fd_stdout = dup(new_fd);
		else if (old_fd == 2)
			job->fd_stderr = dup(new_fd);
		else 
			old_fd = dup(new_fd);;
	}
	if (job->fd_stdin == -1 || job->fd_stdout == -1 || job->fd_stderr == -1
		|| old_fd == -1)
		returnable = -1;
	return (returnable);
}

t_job	*token_greatand(t_job *job, t_term *term, t_node *current)
{
	int		new_fd;
	int		old_fd;
	char	*tkn_word;
	t_job	*returnable;

	returnable = get_left_job(job, current, term);
	if (!returnable)
		return (NULL);
	old_fd = get_fd(current, 1);
	tkn_word = get_filename(current);
	if (ft_strequ(tkn_word, "-"))
	{
		if (-1 == close_fd(returnable, old_fd))
			return (NULL);
	}
	else if (ft_isdigits(tkn_word))
	{
		new_fd = atoi(tkn_word);
		if (-1 == new_fd)
			return(NULL);
		if (-1 == dup_fd(returnable, old_fd, new_fd))
			return (NULL);
	}
	else
	{
		free_job(returnable);
		return (NULL);
	}
	return(returnable);
}