/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:50:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/02 09:26:09 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	is_valid_folder(char *path)
{
	struct stat	buf;

	if (lstat(path, &buf) == -1)
	{
		if (access(path, F_OK))
			return (err_builtin(E_NOENT, "cd", path));
		if (access(path, X_OK))
			return (err_builtin(E_ACCES, "cd", path));
	}
	if ((buf.st_mode & S_IFMT) == S_IFLNK && stat(path, &buf) == -1)
		return (err_builtin(E_LOOP, "cd", path));
	if ((buf.st_mode & S_IFMT) != S_IFDIR)
		return (err_builtin(E_NOTDIR, "cd", path));
	if ((buf.st_mode & S_IXUSR) || (buf.st_mode & S_IXGRP))
		return (0);
	return (err_builtin(E_ACCES, "cd", path));
}
