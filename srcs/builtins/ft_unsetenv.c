/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 21:33:16 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/08 19:39:29 by hhuhtane         ###   ########.fr       */
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
	ft_printf("name=%s len=%d\n", name, len);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
		{
			ft_putendl("UNSETENV DFAOSDFASDF");
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
