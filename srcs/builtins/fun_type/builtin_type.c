/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 20:24:08 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		print_type(char *cmd, t_term *term)
{
	(void)term;
	if (is_builtin_type(cmd))
		ft_printf("%s is a shell builtin\n", cmd);
	return (0);
}

void	builtin_type(void *proc)
{
	t_process	*p;
	int			argc;
	int			i;
	char		**argv;

	p = proc;
	argv = p->argv;
	argc = p->argc;
	i = 0;
	if (argc == 1)
		return ;
	argv++;
	while (*argv)
	{
		print_type(*argv, p->term_ptr);
		argv++;
	}

//	if (argc > 4)
//		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
}
