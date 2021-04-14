/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 11:03:24 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/11 12:25:20 by hhuhtane         ###   ########.fr       */
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

int	find_path(char *file, char *path_env, char *buf)
{
	char	**folders;
	int		i;

	i = 0;
	ft_bzero(buf, 1024);
	folders = ft_strsplit(path_env, ':');
	if (!folders)
		return (-1); // do proper error printing!!!
	while (folders[i])
	{
		if (is_path_file(file, folders[i], buf))
			break ;
		i++;
	}
	if (!folders[i])
		buf[0] = '\0';
	ft_strarray_free(folders); // ok?
	if (buf[0])
		return (1);
	return (0);
}
