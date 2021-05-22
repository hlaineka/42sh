/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:52:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/22 11:57:22 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	builtin_unsetenv(void *proc)
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
		process->status = err_builtin(E_TOO_FEW_ARGS, "unsetenv", NULL);
		ft_printf_fd(2, "usage: unsetenv [name]*\n");
		process->status = 1;
	}
	while (argv[i])
	{
		if (ft_unsetenv(argv[i], envp) == -1)
			process->status = err_builtin(E_INVALID_INPUT, argv[0], argv[i]);
		i++;
	}
	process->completed = 1;
}
