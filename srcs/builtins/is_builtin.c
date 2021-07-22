/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:45:48 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 12:03:35 by hhuhtane         ###   ########.fr       */
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
	&builtin_test
};

int	is_builtin_type(char *cmd)
{
	int		i;

	i = 0;
	while (i < 10 && g_builtins[i])
	{
		if (!ft_strcmp(cmd, g_builtins[i]))
			return (i + 1);
		i++;
	}
	return (0);
}

int	is_builtin(t_process *process)
{
	char	**argv;
	int		i;

	i = 0;
	argv = process->argv;
	while (g_builtins[i])
	{
		if (!ft_strcmp(argv[0], g_builtins[i]))
		{
			process->pid = -1;
			g_builtin_fps[i](process);
			process->completed = 1;
			return (1);
		}
		i++;
	}
	return (0);
}
