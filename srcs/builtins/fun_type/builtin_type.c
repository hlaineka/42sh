/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/21 10:24:36 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int		print_type(char *cmd, t_process *p, t_term *term)
{
	t_hash		*ht;
	char		buf[1024];
	char		*path;

	ht = term->hash_table;
	path = ft_getenv("PATH", p->envp);
	if (is_builtin_type(cmd))
		ft_printf("%s is a shell builtin\n", cmd);
	else if (is_in_hash_table(cmd, term->hash_table))
		ft_printf("%s is hashed (%s%s)\n",
			cmd, cmd_path_from_hash_table(cmd, ht), cmd);
	else
	{
		find_path(cmd, path, buf);
		if (buf[0] == '\0')
			return (err_builtin(E_NO_COMMAND, "type", cmd));
		//if buf is empty error, else this
		ft_printf("%s is a %s\n", cmd, buf);
	}
	return (0);
}

void	builtin_type(void *proc)
{
	t_process	*p;
	int			argc;
	char		**argv;

	p = proc;
	argv = p->argv;
	argc = p->argc;
	if (argc == 1)
		return ;
	argv++;
	while (*argv)
	{
		p->status = print_type(*argv, p, g_term);
		argv++;
	}

//	if (argc > 4)
//		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
}
