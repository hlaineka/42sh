/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:50:33 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 21:21:39 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	print_usage(t_process *process)
{
	process->status = err_builtin(E_TOO_FEW_ARGS, "unset", NULL);
	ft_printf_fd(2, "usage: unset [name]*\n");
}

void	builtin_unset(void *proc)
{
	t_process	*process;
	char		**argv;
	int			i;

	i = 1;
	process = proc;
	argv = process->argv;
	process->status = 0;
	if (process->argc < 2)
		print_usage(process);
	while (argv[i])
	{
		if (argv[i][0] == '-')
		{
			process->status = err_builtin(E_ILLEGAL_OPTION, "unset", NULL);
			break ;
		}
		if (ft_unsetenv(argv[i], g_term->envp) == -1
			|| ft_unsetenv(argv[i], g_term->intern_variables->intern) == -1)
			process->status = err_builtin(E_INVALID_INPUT, argv[0], argv[i]);
		i++;
	}
	process->completed = 1;
}
