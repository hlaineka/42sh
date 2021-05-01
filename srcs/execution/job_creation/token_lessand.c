/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lessand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 14:49:07 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/01 14:58:53 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include <sys/stat.h>
#include <fcntl.h>

static int	dup_fd(int old_fd, char *tkn_word)
{
	int	returnable;
	int	new_fd;

	new_fd = atoi(tkn_word);
	if (new_fd == -1)
		return (-1);
	returnable = close_fd(old_fd);
	if (returnable != -1)
	{
		if (old_fd == 0)
			returnable = dup2(new_fd, STDIN_FILENO);
		else if (old_fd == 1)
			returnable = dup2(new_fd, STDOUT_FILENO);
		else if (old_fd == 2)
			returnable = dup2(new_fd, STDERR_FILENO);
		else
			returnable = dup2(new_fd, old_fd);
	}
	return (returnable);
}

t_job	*token_lessand(t_job *job, t_term *term, t_node *current)
{
	int		old_fd;
	char	*tkn_word;
	t_job	*returnable;

	returnable = get_left_job(job, current, term);
	if (!returnable)
		return (NULL);
	old_fd = get_fd(current, 0);
	tkn_word = get_filename(current);
	if (ft_strequ(tkn_word, "-"))
	{
		if (-1 == close_fd(old_fd))
			return (NULL);
	}
	else if (ft_is_nbrstr(tkn_word))
	{
		if (-1 == dup_fd(old_fd, tkn_word))
			return (NULL);
	}
	else
	{
		free_job(returnable);
		return (NULL);
	}
	return (returnable);
}