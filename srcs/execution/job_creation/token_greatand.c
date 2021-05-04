/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_greatand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/14 16:40:21 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/04 10:36:46 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include <sys/stat.h>
#include <fcntl.h>

static void	dup_fd(int old_fd, char *tkn_word)
{
	int	status;
	int	new_fd;

	new_fd = atoi(tkn_word);
	status = old_fd;
	if (new_fd != old_fd && new_fd != -1)
	{
		status = check_fd(old_fd, 1);
		if (-1 != status || old_fd < 3)
		{
			if (-1 != status)
				status = close_fd(old_fd);
			if (status != -1)
			{
				if (old_fd == 0)
					status = dup2(new_fd, STDIN_FILENO);
				else if (old_fd == 1)
					status = dup2(new_fd, STDOUT_FILENO);
				else if (old_fd == 2)
					status = dup2(new_fd, STDERR_FILENO);
				else
					status = dup2(new_fd, old_fd);
			}
		}
	}
}

t_job	*token_greatand(t_job *job, t_term *term, t_node *current)
{
	int		old_fd;
	char	*tkn_word;
	t_job	*returnable;

	old_fd = get_fd(current, 1);
	tkn_word = get_filename(current);
	if (ft_strequ(tkn_word, "-"))
		close_fd(old_fd);
	else if (ft_is_nbrstr(tkn_word))
		dup_fd(old_fd, tkn_word);
	else
		return (NULL);
	returnable = get_left_job(job, current, term);
	if (!returnable)
		return (NULL);
	return (returnable);
}
