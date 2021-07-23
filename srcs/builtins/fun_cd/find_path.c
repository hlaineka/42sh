/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 11:03:24 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/23 12:46:54 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

/*
** buf=path = memory in stack
*/

static int	is_path_file(char *file, char *folder, char *path)
{
	ft_strcpy(path, folder);
	ft_strcat(path, "/");
	ft_strcat(path, file);
	if (!access(path, F_OK))
		return (1);
	return (0);
}

/*
** 	if (!folders)
**		return (-1); // do proper error printing!!!
*/

char	*find_path_for_cmd(char *cmd, char **envp, const char *fn)
{
	char	buf[1024];
	char	**folders;
	char	**temp;
	char	*path;

	path = ft_getenv("PATH", envp);
	if (!path)
	{
		err_builtin(E_ENV_PATH_NOT_SET, (char *)fn, NULL);
		return (NULL);
	}
	folders = ft_strsplit(path, ':');
	path = NULL;
	if (!folders)
		err_builtin(E_NOMEM, (char *)fn, NULL);
	temp = folders;
	while (folders && *folders)
	{
		if (path == NULL && is_path_file(cmd, *folders, buf))
			path = *folders;
		else
			free(*folders);
		folders++;
	}
	free(temp);
	if (path == NULL)
		err_builtin(E_NOT_FOUND, (char *)fn, cmd);
	return (path);
}

int	find_path(char *file, char *path_env, char *buf)
{
	char	**folders;
	int		i;

	i = 0;
	ft_bzero(buf, 1024);
	folders = ft_strsplit(path_env, ':');
	if (!folders)
		return (-1);
	while (folders[i])
	{
		if (is_path_file(file, folders[i], buf))
			break ;
		i++;
	}
	if (!folders[i])
		buf[0] = '\0';
	ft_strarray_free(folders);
	if (buf[0])
		return (1);
	return (0);
}
