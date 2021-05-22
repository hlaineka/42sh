/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:50:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/22 13:33:18 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	is_valid_folder(char *path, char *progname)
{
	struct stat	buf;

	if (stat(path, &buf) == -1 || lstat(path, &buf) == -1)
	{
		if (access(path, F_OK))
			return (err_builtin(E_NOENT, progname, path));
		if (access(path, X_OK))
			return (err_builtin(E_ACCES, progname, path));
	}
	if (access(path, F_OK))
		return (err_builtin(E_NOENT, progname, path));
	if (access(path, X_OK))
		return (err_builtin(E_ACCES, progname, path));
	if ((buf.st_mode & S_IFMT) == S_IFLNK && stat(path, &buf) == -1)
		return (err_builtin(E_LOOP, progname, path));
	if ((buf.st_mode & S_IFMT) != S_IFDIR)
		return (err_builtin(E_NOTDIR, progname, path));
	if ((buf.st_mode & S_IXUSR) || (buf.st_mode & S_IXGRP))
		return (0);
	return (err_builtin(E_ACCES, progname, path));
}
