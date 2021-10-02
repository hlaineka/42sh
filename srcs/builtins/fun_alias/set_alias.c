/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_alias.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/28 20:19:36 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/10/02 14:40:37 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static int	is_unvalid_name(const char *name)
{
	if (ft_strequ(name, ""))
		return (err_builtin(E_INVALID_INPUT, "alias", NULL));
	if (name[0] == '-')
		return (err_builtin(E_ILLEGAL_OPTION, "alias", NULL));
	if (!ft_is_name((char *)name))
		return (err_builtin(E_INVALID_INPUT, "alias", NULL));
	return (0);
}

static int	replace_alias(int i, const char *value, t_alias *alias)
{
	ft_memdel(&alias[i].value);
	if (!value)
		alias[i].value = ft_strnew(0);
	else
		alias[i].value = ft_strdup(value);
	if (!alias[i].value)
		return (err_builtin(E_NOMEM, "alias", NULL));
	return (0);
}

int	set_alias(const char *name, const char *value, t_alias *alias)
{
	int		i;

	i = 0;
	if (is_unvalid_name(name))
		return (1);
	while (i < ALIAS_SIZE && alias[i].name)
	{
		if (ft_strequ(alias[i].name, name))
			return (replace_alias(i, value, alias));
		i++;
	}
	alias[i].name = ft_strdup(name);
	if (!alias[i].name)
		return (err_builtin(E_NOMEM, "alias", NULL));
	alias[i].value = ft_strdup(value);
	if (!alias[i].value)
	{
		free(alias[i].name);
		return (err_builtin(E_NOMEM, "alias", NULL));
	}
	return (0);
}

int	unset_alias(const char *name, t_alias *alias)
{
	int		i;
	int		unset;

	i = 0;
	unset = 1;
	while (i < ALIAS_SIZE && alias[i].name)
	{
		if (unset && ft_strequ(alias[i].name, name))
		{
			free(alias[i].name);
			alias[i].name = alias[i + 1].name;
			free(alias[i].value);
			alias[i].value = alias[i + 1].value;
			unset = 0;
		}
		else if (!unset)
		{
			alias[i].name = alias[i + 1].name;
			alias[i].value = alias[i + 1].value;
		}
		i++;
	}
	return (0);
}
