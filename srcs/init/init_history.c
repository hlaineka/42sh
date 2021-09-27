/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:39:57 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/27 18:11:21 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "init.h"
#include "builtins.h"

int	open_history_file(t_term *term, int oflag)
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
	fd = open(buf, oflag, 0666);
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
	term->history[i + 1] = NULL;
}

int	write_history_to_file(int fd, t_term *term)
{
	int		i;

	i = 1;
	while (i < HISTORY_SIZE && term->history[i])
	{
		ft_printf_fd(fd, "%s\n", term->history[i]);
		i++;
	}
	return (0);
}

static int	read_history_to_memory(int fd, t_term *term)
{
	int		i;
	int		ret;
	char	*line;

	i = 1;
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		if (i < HISTORY_SIZE - 1)
			term->history[i++] = line;
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
	{
		close(fd);
		return ;
	}
	read_history_to_memory(fd, term);
	close(fd);
}
