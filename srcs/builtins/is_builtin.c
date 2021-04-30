/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 18:45:48 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/30 11:15:13 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static const char	*g_builtins[] =
{
	"cd",
	"echo",
	"env",
//	"exit",
	"setenv",
	"unsetenv"
};

static const t_fp	g_builtin_fps[] =
{
	&builtin_cd,
	&builtin_echo,
	&builtin_env,
//	&builtin_exit,
	&builtin_setenv,
	&builtin_unsetenv
};

int	is_builtin(t_process *process)
{
	char	**argv;
	int		i;

	i = 0;
	argv = process->argv;
	while (g_builtins[i])
	{
//		ft_printf("%s %s\n", argv[1], g_builtins[i]);
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
