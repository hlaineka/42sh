/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/21 10:27:30 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** UNALIAS:
**   The unalias utility shall remove the definition for each alias name
**   specified. See Alias Substitution. The aliases shall be removed from
**   the current shell execution environment;
*/

static void	remove_all_aliases(t_alias *alias)
{
	int		i;

	i = 0;
	while (i < ALIAS_SIZE && alias[i].name)
	{
		ft_printf("unalias %s='%s' ", alias[i].name, alias[i].value); //todo remove
		free(alias[i].name);
		alias[i].name = NULL;
		free(alias[i].value);
		alias[i].value = NULL;
//		unset_alias(alias[i].name, alias);
		ft_putendl("removed"); // todo remove
		i++;
	}
}

/*
** FIND_ALIAS_NAMED_NAME function finds alias value for the alias NAME.
**   if no alias NAME is found, it returns NULL. Return string is const so
**   it shouldn't be freed. make a copy from the return value if needed.!
*/

/*
const char *find_alias_named_name(const char *name, t_alias *alias)
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
*/

/*
static void	print_alias(const char *name, t_process *p, t_term *term)
{
	const char	*value;

	if (name == NULL)
		print_all_aliases(term->alias);
	else
	{
		value = find_alias_named_name(name, term->alias);
		if (!value)
		{
			p->status = 1;
			return ;
		}
		p->status = 0;
		ft_printf("alias %s='%s'\n", name, value);
	}
}
*/

static void	unalias_react_to_arg(char *arg, t_process *p, t_term *term)
{
	if (arg)
	{
		p->status = unset_alias(arg, term->alias);
	}
	else
	{
		p->status = 1;
		ft_printf_fd(STDERR_FILENO, "42sh: unalias: %s: not found");
	}
}

void	builtin_unalias(void *proc)
{
	t_term	*term;
	int		argc;
	int		i;
	char	**argv;

	i = 1;
	term = g_term;
	argc = ((t_process *)proc)->argc;
	argv = ((t_process *)proc)->argv;
	if (argc == 1)
	{
		((t_process *)proc)->status = 1;
		ft_printf_fd(STDERR_FILENO , "42sh: unalias: usage: unalias [-a] name [name ...]\n");
		return ;
	}
	if (ft_strequ(argv[1], "-a"))
		return (remove_all_aliases(term->alias));
	while (i < argc)
	{
		unalias_react_to_arg(argv[i], proc, term);
		i++;
	}
}
