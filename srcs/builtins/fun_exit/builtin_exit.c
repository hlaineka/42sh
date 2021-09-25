/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/25 16:20:31 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "builtins.h"
#include "init.h"

static int	is_num_str(char *str)
{
	while (str && *str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

int	save_history_to_file_and_exit(t_term *term, int exit_status)
{
	int			fd;

	fd = open_history_file(term, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		exit(err_builtin(E_BADF, "OPEN", NULL));
	write_history_to_file(fd, term);
	close(fd);
	exit(exit_status);
	return (0);
}

void	builtin_exit(void *proc)
{
	t_process	*process;
	char		**argv;
	int			argc;
	int			ret;

	ret = 0;
	ft_printf_fd(STDERR_FILENO, "exit\n");
	process = proc;
	argv = process->argv;
	argc = process->argc;
	if (argc > 2)
	{
		ft_printf_fd(STDERR_FILENO, "42sh: exit: too many arguments\n");
		process->status = 1;
		return ;
	}
	if (argc == 2 && !is_num_str(argv[1]))
	{
		ft_printf_fd(STDERR_FILENO,
			"42sh: %s: numeric argument reguired\n", argv[1]);
		ret = 255;
	}
	else if (argc == 2)
		ret = ft_atoi(argv[1]);
	exit(save_history_to_file_and_exit(g_term, ret));
}
