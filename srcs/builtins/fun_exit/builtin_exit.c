/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/02 19:29:01 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

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
		ft_printf_fd(STDERR_FILENO, "21sh: exit: too many arguments\n");
		process->status = 1;
		return ;
	}
	if (argc == 2 && !is_num_str(argv[1]))
	{
		ft_printf_fd(STDERR_FILENO,
			"21sh: %s: numeric argument reguired\n", argv[1]);
		ret = 255;
	}
	else if (argc == 2)
		ret = ft_atoi(argv[1]);
	exit(ret);
}
