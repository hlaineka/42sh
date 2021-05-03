/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dless.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:45:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/03 16:31:57 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "input.h"
#include "libft.h"
#include "execution.h"
#include <sys/stat.h>
#include <fcntl.h>

/*
**
*/

int	redirect_heredoc(t_node *current, t_term *term)
{
	char	*delimiter;
	char	*output;
	int		fd;

	output = NULL;
	delimiter = get_filename(current);
	delimiter = ft_strjoin_all(delimiter, "\n", 0);
	output = get_input_heredoc(delimiter, term->here_input, term);
	fd = open("temp_files/heredoc.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU
			| S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
	if (fd != -1)
	{
		write(fd, output, ft_strlen(output));
		write(fd, "\n", 1);
		close(fd);
		if (-1 != fd)
			fd = open("temp_files/heredoc.txt", O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	ft_free(output);
	ft_free(delimiter);
	return (fd);
}

t_job	*token_dless(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;
	int		fd;

	if (!current->left)
		return (NULL);
	returnable = NULL;
	fd = redirect_heredoc(current, term);
	term->heredoc_fd = fd;
	if (-1 == fd)
		return (NULL);
	returnable = get_left_job(job, current, term);
	return (returnable);
}
