/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_alias.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/21 11:57:48 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** ALIAS:
** `alias' with no arguments prints the list
**  of aliases in the form alias NAME=VALUE on standard output.
**  Otherwise, an alias is defined for each NAME whose VALUE is given.
**  A trailing space in VALUE causes the next word to be checked for
**  alias substitution when the alias is expanded.  Alias returns
**  true unless a NAME is given for which no alias has been defined.
*/

static void	print_all_aliases(t_alias *alias)
{
	int		i;

	i = 0;
	while (i < ALIAS_SIZE && alias[i].name)
	{
		ft_printf("alias %s='%s'\n", alias[i].name, alias[i].value);
		i++;
	}
}

/*
** FIND_ALIAS_NAMED_NAME function finds alias value for the alias NAME.
**   if no alias NAME is found, it returns NULL. Return string is const so
**   it shouldn't be freed. make a copy from the return value if needed.!
*/

const char *find_alias_named_name(const char *name, t_alias *alias)
{
	int		i;

	i = 0;
	while (i < ALIAS_SIZE && alias[i].name)
	{
		if (ft_strequ(alias[i].name, name))
		{
			if (alias[i].state == 1)
				return (NULL);
			alias[i].state = 1;
//			if (!alias[i].value)
//				return ("");
			return (alias[i].value);
		}
		i++;
	}
	return (NULL);
}

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

static void	alias_react_to_arg(char *arg, t_process *p, t_term *term)
{
	char	*split;

	split = ft_strchr(arg, '=');
	if (split)
	{
		*split = '\0';
		p->status = set_alias(arg, split + 1, term->alias);
		*split = '=';
	}
	else
		print_alias(arg, p, term);
}

void	builtin_alias(void *proc)
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
		return (print_alias(NULL, proc, term));
	while (i < argc)
	{
		alias_react_to_arg(argv[i], proc, term);
		i++;
	}
}
