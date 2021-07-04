/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_fg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/02 20:48:01 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void	builtin_fg(void *proc)
{
	t_term		*term;
	t_process	*process;
	char		**argv;
	int			i;

	process = proc;
	term = process->term_ptr;
	argv = process->argv;
	i = 1;
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
