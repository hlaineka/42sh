/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_absolute_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:40:06 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/27 21:14:44 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

char	*get_absolute_path_to_buf(char *rel, char **envp, char *buf)
{
	char	*cdpath;

	if (is_absolute_path(rel))
		return (ft_strcpy(buf, rel));
	cdpath = ft_getenv("CDPATH", envp);
	if (!cdpath)
		cdpath = ft_getenv("CDPATH", g_term->intern_variables->intern);
	if (cdpath && find_path(rel, cdpath, buf))
		return (buf);
	buf = getcwd(buf, 1024);
	if (ft_strcmp("/", buf))
		buf = ft_strcat(buf, "/");
	buf = ft_strcat(buf, rel);
	return (buf);
}
