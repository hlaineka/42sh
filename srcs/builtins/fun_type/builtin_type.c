/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/27 18:06:51 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static char	*find_path_env(t_process *p, t_term *term)
{
	char	*path;

	path = ft_getenv("PATH", p->envp);
	if (!path)
		path = ft_getenv("PATH", term->intern_variables->intern);
	return (path);
}

int	print_type(char *cmd, t_process *p, t_term *term)
{
	t_hash		*ht;
	char		buf[1024];
	char		*path;

	ht = term->hash_table;
	path = find_path_env(p, term);
	if (is_builtin_type(cmd))
		ft_printf("%s is a shell builtin\n", cmd);
	else if (is_in_hash_table(cmd, term->hash_table))
		ft_printf("%s is hashed (%s/%s)\n",
			cmd, cmd_path_from_hash_table(cmd, ht), cmd);
	else
	{
		if (!cmd[0])
			return (err_builtin(E_NO_COMMAND, "type", cmd));
		find_path(cmd, path, buf);
		if (buf[0] == '\0')
			return (err_builtin(E_NO_COMMAND, "type", cmd));
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
		if (*argv[0] == '-')
			p->status = err_builtin(E_ILLEGAL_OPTION, "type", NULL);
		else
			p->status = print_type(*argv, p, g_term);
		if (p->status)
			return ;
		argv++;
	}
}
