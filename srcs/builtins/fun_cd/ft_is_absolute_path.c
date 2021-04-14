/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_absolute_path.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:10:29 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/06 18:11:50 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

int	is_absolute_path(char *path)
{
	if (!path)
		return (0);
	if (path[0] == '/')
		return (1);
	if (path[0] == '.'
		&& ((path[1] == '\0' || path[1] == '/')
			|| (path[1] == '.' && (path[2] == '\0' || path[2] == '/'))))
		return (1);
	return (0);
}
