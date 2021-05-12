/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/08 17:31:02 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static int	validate_stdout(t_process *process)
{
	if (check_fd(STDOUT_FILENO, 0) == -1)
	{
		ft_printf_fd(STDERR_FILENO, "21sh: echo: ");
		ft_printf_fd(STDERR_FILENO, "write error: Bad file descriptor\n");
		process->completed = 1;
		process->status = 1;
		return (1);
	}
	return (0);
}

void	builtin_echo(void *proc)
{
	t_process	*process;
	char		**argv;
	int			i;

	process = proc;
	argv = process->argv;
	i = 1;
	if (validate_stdout(proc))
		return ;
	if (argv[1] && !ft_strcmp(argv[1], "-n"))
		i++;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		i++;
		if (argv[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (!argv[1] || ft_strcmp(argv[1], "-n"))
		ft_putchar_fd('\n', STDOUT_FILENO);
	process->completed = 1;
	process->status = 0;
}
