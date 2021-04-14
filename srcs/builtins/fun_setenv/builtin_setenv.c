/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 17:52:24 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/07 18:16:26 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	builtin_setenv(void *proc)
{
	t_process	*process;
	int			argc;
	char		**argv;
	char		**envp;

	process = proc;
	argc = process->argc;
	argv = process->argv;
	envp = process->envp;
	if (argc == 1 || argc > 3 || ft_strlen(argv[1]) < 1)
	{
		process->status = err_builtin(E_INVALID_INPUT, argv[0], NULL);
		ft_printf_fd(2, "usage: setenv [name] [value]\n");
	}
	else if (argc == 2)
		process->status = ft_setenv(argv[1], "", 1, envp);
	else
		process->status = ft_setenv(argv[1], argv[2], 1, envp);
	process->completed = 1;
}
