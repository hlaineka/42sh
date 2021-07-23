/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_set.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 20:53:10 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/22 21:27:24 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "includes.h"

int print_intern_variables(void)
{
	t_term	*term;
	char	**intern;
	int		i;

	term = g_term;
	intern = term->intern_variables->intern;
	i = 0;
	ft_printf("debug=%i\n", term->intern_variables->flag_debug);
	ft_printf("noclobber=%i\n", term->intern_variables->flag_noclobber);
	ft_printf("rawmode=%i\n", term->intern_variables->flag_rawmode);
	while(intern[i])
	{
		ft_printf("%s\n", intern[i]);
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
		errors = print_intern_variables();
	else
		errors = 1;
	if (errors)
	{
		process->status = err_builtin(E_INVALID_INPUT, argv[0], NULL);
		ft_printf_fd(2, "usage: set to print internal variables. No flags.\n");
	}
	process->completed = 1;
}