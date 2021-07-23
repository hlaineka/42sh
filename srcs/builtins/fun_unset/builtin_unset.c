/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:50:33 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/22 21:24:30 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	builtin_unset(void *proc)
{
	t_process	*process;
	int			argc;
	char		**argv;
	char		**envp;
	int			i;

	i = 1;
	process = proc;
	argc = process->argc;
	argv = process->argv;
	envp = process->envp;
	process->status = 0;
	if (argc < 2)
	{
		process->status = err_builtin(E_TOO_FEW_ARGS, "unset", NULL);
		ft_printf_fd(2, "usage: unset [name]*\n");
	}
	while (argv[i])
	{
		if (ft_getenv(argv[i], g_term->envp))
		{
			if (ft_unsetenv(argv[i], g_term->envp) == -1)
				process->status = err_builtin(E_INVALID_INPUT, argv[0], argv[i]);
		}
		else if (ft_unsetenv(argv[i], g_term->intern_variables->intern) == -1)
			process->status = err_builtin(E_INVALID_INPUT, argv[0], argv[i]);
		i++;
	}
	process->completed = 1;
}