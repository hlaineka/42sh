/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:54:24 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/22 21:17:43 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "includes.h"

void	builtin_export(void *proc)
{
	t_process	*process;
	char		**argv;
	int			i;
	char		name[STR_LENGTH];
	char		value[STR_LENGTH];

	process = proc;
	argv = process->argv;
	if (process->argc == 1)
		print_envp(g_term->envp);
	i = 1;
	while (argv[i])
	{
		ft_bzero(name, STR_LENGTH);
		ft_bzero(value, STR_LENGTH);
		if (0 == get_name_and_value(argv[i], value, name))
		{
			process->status = err_builtin(E_INVALID_INPUT, "export", NULL);
			ft_printf_fd(2, "usage: export [name]=[value] or export to list env variables\n");
		}
		process->status = ft_setenv(name, value, 1, g_term->envp);
		if (process->status)
			err_builtin(process->status, argv[0], argv[1]);
		i++;
	}
	process->completed = 1;
}