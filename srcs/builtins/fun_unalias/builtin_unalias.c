/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unalias.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/26 21:30:52 by hhuhtane         ###   ########.fr       */
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
		free(alias[i].name);
		alias[i].name = NULL;
		free(alias[i].value);
		alias[i].value = NULL;
		i++;
	}
}

static void	unalias_react_to_arg(char *arg, t_process *p, t_term *term)
{
	if (arg && arg[0] == '-')
	{
		p->status = 1;
		ft_printf_fd(STDERR_FILENO, "42sh: unalias: %s: illegal option\n");
	}
	else if (arg)
		p->status = unset_alias(arg, term->alias);
	else
	{
		p->status = 1;
		ft_printf_fd(STDERR_FILENO, "42sh: unalias: %s: not found\n");
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
		ft_printf_fd(STDERR_FILENO,
			"42sh: unalias: usage: unalias [-a] name [name ...]\n");
		return ;
	}
	if (ft_strequ(argv[1], "-a"))
		return (remove_all_aliases(term->alias));
	while (i < argc)
	{
		unalias_react_to_arg(argv[i], proc, term);
		if (((t_process *)proc)->status)
			return ;
		i++;
	}
}
