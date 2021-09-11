/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_alias.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:43:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/11 16:43:33 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** FIND_ALIAS_NAMED_NAME function finds alias value for the alias NAME.
**   if no alias NAME is found, it returns NULL. Return string is const so
**   it shouldn't be freed. make a copy from the return value if needed.!
*/

t_alias	*find_alias_with_name(const char *name, t_alias *alias)
{
	int		i;

	i = 0;
	while (i < ALIAS_SIZE && alias[i].name)
	{
		if (ft_strequ(alias[i].name, name))
			return (&alias[i]);
		i++;
	}
	return (NULL);
}

const char	*find_alias_named_name(const char *name, t_alias *alias)
{
	int		i;

	i = 0;
	while (i < ALIAS_SIZE && alias[i].name)
	{
		if (ft_strequ(alias[i].name, name))
			return (alias[i].value);
		i++;
	}
	return (NULL);
}
