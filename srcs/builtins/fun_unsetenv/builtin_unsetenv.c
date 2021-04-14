/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unsetenv.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:52:15 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/08 19:44:19 by hhuhtane         ###   ########.fr       */
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
	if (argc < 2)
	{
		process->status = err_builtin(E_TOO_FEW_ARGS, "unsetenv", NULL);
		ft_printf_fd(2, "usage: unsetenv [name]*\n");
	}
	while (argv[i])
	{
		if (ft_unsetenv(argv[i], envp) == -1)
			process->status = err_builtin(ERR_INVALID_INPUT, argv[0], argv[i]);
		i++;
	}
	process->completed = 1;
	process->status = 0;
}
