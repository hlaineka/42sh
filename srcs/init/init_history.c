/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:39:57 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/25 15:15:31 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "init.h"
#include "builtins.h"

static int	open_history_file(t_term *term, int oflag)
{
	char	buf[1024];
	char	*home;
	int		fd;

	fd = 0;
	ft_bzero(buf, sizeof(char) * 1024);
	home = ft_getenv("HOME", term->envp);
	if (!home)
		return (-1);
	write_path_to_buffer(buf, home, ".42sh_history");
	fd = open(buf, oflag);
	return (fd);
}

void	remove_oldest_and_move(t_term *term, char *cmd)
{
	int		i;

	i = 1;
	free(term->history[1]);
	while (i < HISTORY_SIZE - 2)
	{
		i++;
		term->history[i - 1] = term->history[i];
	}
	term->history[i] = cmd;
}

static int	read_history_to_memory(int fd, t_term *term)
{
	int		i;
	int		ret;
	char	*line;

	i = 1;
	ret = get_next_line(fd, &line);
	while(ret > 0)
	{
		if (i < HISTORY_SIZE - 2)
		{
			term->history[i++] = line;
		}
		else
			remove_oldest_and_move(term, line);
		ret = get_next_line(fd, &line);
	}
	if (line)
		free(line);
	return (0);
}

void	init_history(t_term *term)
{
	int		fd;

	fd = open_history_file(term, O_RDONLY);
	if (fd == -1)
		return ((void)err_builtin(E_BADF, "OPEN", NULL));
	read_history_to_memory(fd, term);
	close(fd);
}