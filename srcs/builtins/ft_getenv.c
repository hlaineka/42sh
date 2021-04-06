/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 17:17:00 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/06 13:46:51 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

/*
** The getenv() function obtains the current value of the environment vari-
** able, name.  The application should not modify the string pointed to by the
** ft_getenv() function.
*/

char	*ft_getenv(const char *name, char **envp)
{
	size_t		len;
	int			i;

	i = 0;
	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + (len + 1));
		i++;
	}
	return (NULL);
}
