/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:53:10 by hlaineka          #+#    #+#             */
/*   Updated: 2021/09/27 17:24:25 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "includes.h"

int	print_intern_variables(char **variables)
{
	t_term		*term;
	int			i;

	term = g_term;
	i = 0;
	ft_printf("debug=%i\n", term->intern_variables->flag_debug);
	ft_printf("noclobber=%i\n", term->intern_variables->flag_noclobber);
	ft_printf("rawmode=%i\n", term->intern_variables->flag_rawmode);
	while (variables[i])
	{
		ft_printf("%s\n", variables[i]);
		i++;
	}
	return (0);
}

static int	is_in_envp(char *var, char **envp)
{
	int			i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strcmp(var, envp[i]))
			return (1);
		i++;
	}
	return (0);
}

static int	print_env_and_internal(void)
{
	char		**vars;
	char		**envp;
	int			i;

	i = 0;
	vars = g_term->intern_variables->intern;
	envp = g_term->envp;
	while (vars[i])
	{
		if (!is_in_envp(vars[i], envp))
			ft_printf("%s\n", vars[i]);
		i++;
	}
	return (0);
}

void	builtin_set(void *proc)
{
	t_process	*process;
	char		**argv;
	int			errors;

	errors = 0;
	process = proc;
	argv = process->argv;
	process->status = 0;
	if (process->argc == 1)
	{
		errors = print_intern_variables(g_term->envp);
		errors = print_env_and_internal();
	}
	else if (process->argc == 2 && !ft_strcmp(process->argv[1], "-i"))
		errors = print_intern_variables(g_term->intern_variables->intern);
	else
		errors = 1;
	if (errors)
	{
		process->status = err_builtin(E_INVALID_INPUT, argv[0], NULL);
		ft_printf_fd(2, "usage: set to print internal variables..\n");
		ft_printf_fd(2, "\t optional: flag -i to print only internal.\n");
	}
	process->completed = 1;
}
