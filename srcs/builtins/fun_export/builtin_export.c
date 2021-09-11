/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:54:24 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/11 14:09:13 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "includes.h"

static int	export_p_option(char **envp)
{
	char		*split;

	while (*envp)
	{
		split = ft_strchr(*envp, '=');
		*split = '\0';
		ft_printf_fd(STDOUT_FILENO,
			"export %s=%s\n", envp[0], split + 1);
		*split = '=';
		envp++;
	}
	return (0);
}

void	builtin_export(void *proc)
{
	t_process	*process;
	int			i;
	char		name[STR_LENGTH];
	char		value[STR_LENGTH];

	process = proc;
	if (process->argc == 1)
	{
		if (process->envp)
			print_envp(process->envp);
		else
			print_envp(g_term->envp);
	}
	i = 1;
	if (process->argc == 2 && ft_strequ(process->argv[1], "-p"))
		return ((void)export_p_option(g_term->envp));
	while (process->argv[i])
	{
		ft_bzero(name, STR_LENGTH);
		ft_bzero(value, STR_LENGTH);
		if (ft_strchr(process->argv[i], '=')
			&& 0 == get_name_and_value(process->argv[i], value, name))
		{
			process->status = err_builtin(E_INVALID_INPUT, "export", NULL);
			ft_printf_fd(2, "usage: export [name]=[value] or export to list env variables\n");
		}
		else
		{
			ft_strcpy(name, process->argv[i]);
			ft_strcpy(value, ft_getenv(name, g_term->intern_variables->intern));
		}
		ft_setenv(name, value, 0, g_term->intern_variables->intern);
		process->status = ft_setenv(name, value, 1, g_term->envp);
		if (process->status)
			err_builtin(process->status, process->argv[0], process->argv[1]);
		i++;
	}
	process->completed = 1;
}
