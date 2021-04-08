/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/08 17:59:20 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	builtin_echo(void *proc)
{
	t_process	*process;
	char		**argv;
	int		i;

	process = proc;
	argv = process->argv;
	i = 1;
	if (argv[1] && !ft_strcmp(argv[1], "-n"))
		i++;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		i++;
		if (argv[i])
			ft_putchar(' ');
	}
	if (!argv[1] || ft_strcmp(argv[1], "-n"))
		ft_putchar('\n');
	process->completed = 1;
//	process->stopped = 1;
	process->status = 0;
}
