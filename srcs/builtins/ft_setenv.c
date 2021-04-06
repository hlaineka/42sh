/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 20:06:23 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/06 13:40:20 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

/*
** The ft_setenv() function inserts or resets the environment variable name in
** the current environment list.  If the variable name does not exist in the
** list, it is inserted with the given value.  If the variable does exist, the
** argument over is tested; if overwrite is zero, the variable is not reset,
** otherwise the old is freed and new is set to the given value.
**
** The setenv() function return the value 0 if successful; otherwise the
** negative value is returned. Negative errno value is to indicate which the
** error it was.
*/

static char	*make_new_env_str(const char *name, const char *val)
{
	char		*new;
	size_t		name_len;
	size_t		val_len;

	name_len = ft_strlen(name);
	val_len = ft_strlen(val);
	new = ft_memalloc(name_len + 1 + val_len + 1);
	if (!new)
		return (NULL);
	ft_strcat(new, name);
	new[name_len] = '=';
	ft_strcat(new, val);
	return (new);
}

int	ft_setenv(const char *name, const char *val, int over, char **envp)
{
	char		*new;
	size_t		len;
	int			i;

	i = 0;
	len = ft_strlen(name);
	if (!name || ft_strchr(name, '='))
		return (-E_INVAL);
	if (ft_getenv(name, envp) && !over)
		return (0);
	new = make_new_env_str(name, val);
	if (!new)
		return (-E_NOMEM);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
		{
			free(envp[i]);
			envp[i] = new;
			return (0);
		}
		i++;
	}
	envp[i++] = new;
	return (0);
}
