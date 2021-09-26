/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:33:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/26 08:20:01 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

/*
** The ft_unsetenv() function deletes all instances of the variable name
** pointed to by name from the list.  Note that only the variable name
** (e.g., "NAME") should be given; "NAME=value" will not work.
*/

int	ft_unsetenv(const char *name, char **envp)
{
	size_t	len;
	int		i;

	i = 0;
	if (!name || ft_strchr(name, '='))
		return (-E_INVAL);
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
		{
			free(envp[i]);
			break ;
		}
		i++;
	}
	while (envp[i])
	{
		envp[i] = envp[i + 1];
		i++;
	}
	return (0);
}
