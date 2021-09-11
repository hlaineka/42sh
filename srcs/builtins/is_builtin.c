/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:45:48 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/11 18:12:35 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static const char	*g_builtins[] = {
	"cd",
	"echo",
	"env",
	"setenv",
	"unsetenv",
	"fg",
	"jobs",
	"bg",
	"fc",
	"test",
	"type",
	"hash",
	"export",
	"set",
	"unset",
	"alias",
	"unalias",
	"exit",
	NULL
};

static const t_fp	g_builtin_fps[] = {
	&builtin_cd,
	&builtin_echo,
	&builtin_env,
	&builtin_setenv,
	&builtin_unsetenv,
	&builtin_fg,
	&builtin_jobs,
	&builtin_bg,
	&builtin_fc,
	&builtin_test,
	&builtin_type,
	&builtin_hash,
	&builtin_export,
	&builtin_set,
	&builtin_unset,
	&builtin_alias,
	&builtin_unalias,
	&builtin_exit,
	NULL
};

int	is_builtin_type(char *cmd)
{
	int		i;

	i = 0;
	while (g_builtins[i])
	{
		if (!ft_strcmp(cmd, g_builtins[i]))
			return (i + 1);
		i++;
	}
	return (0);
}

int	is_builtin(t_process *process)
{
	int		i;
	int		set;

	i = 0;
	set = 0;
	while (g_builtins[i])
	{
		if (!ft_strcmp(process->argv[0], g_builtins[i]))
		{
			process->pid = -1;
			if (!process->envp)
			{
				process->envp = g_term->envp;
				set = 1;
			}
			g_builtin_fps[i](process);
			process->completed = 1;
			if (set)
				process->envp = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}
