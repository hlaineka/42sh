/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/20 20:54:24 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/26 12:21:10 by hhuhtane         ###   ########.fr       */
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

static int	export_arg(char *arg, t_process *process, t_term *term)
{
	char		name[STR_LENGTH];
	char		value[STR_LENGTH];

	ft_bzero(name, STR_LENGTH);
	ft_bzero(value, STR_LENGTH);
	if (!ft_strchr(arg, '='))
	{
		ft_strcpy(name, arg);
		if (!ft_getenv(name, term->intern_variables->intern))
			return (0);
		ft_strcpy(value, ft_getenv(name, term->intern_variables->intern));
	}
	else if (ft_strchr(arg, '=') && 0 == get_name_and_value(arg, value, name))
	{
		process->status = err_builtin(E_INVALID_INPUT, "export", NULL);
		ft_printf_fd(2,
			"usage: export [name]=[value] or export to list env variables\n");
		return (1);
	}
	ft_setenv(name, value, 0, term->intern_variables->intern);
	process->status = ft_setenv(name, value, 1, term->envp);
	if (process->status)
		return (err_builtin(E_EXPORT_FAIL, "export", arg));
	return (0);
}

void	builtin_export(void *proc)
{
	t_process	*process;
	int			i;

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
		if (export_arg(process->argv[i], process, g_term))
		{
			g_term->last_return = 1;
			process->status = 1;
			break ;
		}
		i++;
	}
	process->completed = 1;
}
