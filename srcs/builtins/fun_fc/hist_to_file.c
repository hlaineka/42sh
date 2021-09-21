/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hist_to_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 19:49:17 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/20 20:30:13 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"

static int	write_path_to_file(char *buf, char *path, char *file)
{
	ft_strcpy(buf, path);
	ft_strcat(buf, "/");
	ft_strcat(buf, file);
	return (0);
}

static int	open_temp_file_write(t_term *term)
{
	char	path[1024];
	char	*home;
	int		fd;

	ft_bzero(path, sizeof(char) * 1024);
	home = ft_getenv("HOME", term->envp);
	if (!home)
		return (-1);
	write_path_to_file(path, home, ".42sh_oldies_temp");
	fd = open(path, O_WRONLY | O_CREAT | O_TRUNC);
	return (fd);
}

static int	open_temp_file_read(t_term *term)
{
	char	path[1024];
	char	*home;
	int		fd;

	ft_bzero(path, sizeof(char) * 1024);
	home = ft_getenv("HOME", term->envp);
	if (!home)
		return (-1);
	write_path_to_file(path, home, ".42sh_oldies_temp");
	fd = open(path, O_RDONLY);
	return (fd);
}

int	hist_to_file(t_fc *fc, char **hist, t_term *term, t_process *proc)
{
	char	path[1024];
	int		i;
	int		fd;
	char	*line;
	int		ret;

	line = NULL;
	write_path_to_file(path, ft_getenv("HOME", term->envp), ".42sh_oldies_temp");
	proc->argv[2] = path;
	proc->envp = term->envp;
	fd = open_temp_file_write(term);
	if (fc->first)
		i = fc->first;
	else
		i = get_last_history_index(hist) - 1;
	while (i <= fc->last)
		ft_printf_fd(fd, "%s\n", hist[i++]);
	close(fd);
	builtin_env(proc);
	fd = open_temp_file_read(term);
	ret = get_next_line(fd, &line);
	while (ret > 0)
	{
		parse_and_execute(line, term);
		ret = get_next_line(fd, &line);
	}
	close(fd);
	if (line)
		free(line);
	return (1);
}
