/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 20:42:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		print_type(char *cmd, t_process *p, t_term *term)
{
	char		buf[1024];
	char		*path;

	(void)term;
	path = ft_getenv("PATH", p->envp);
	if (is_builtin_type(cmd))
		ft_printf("%s is a shell builtin\n", cmd);
	else
	{
		find_path(cmd, path, buf);
		ft_printf("%s is a %s\n", cmd, buf);
	}
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
		print_type(*argv, p, p->term_ptr);
		argv++;
	}

//	if (argc > 4)
//		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
}
