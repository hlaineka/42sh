/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:22:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/02 13:03:19 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

//int	builtin_cd(int argc, char **argv, char **envp)

void	builtin_cd(void *proc)
{
	t_process	*process;
	int			argc;
	char		**argv;
	char		**envp;
	process = proc;
	envp = process->envp;
	argv = process->argv;
	argc = process->argc;

	char	path[1024];
	char	cwd[1024];

	if (argc > 2)
	{
		err_builtin(E_TOO_MANY_ARGS, argv[0], NULL);
		return ;
//		return (err_builtin(E_TOO_MANY_ARGS, argv[0], NULL));
	}
	if (argc == 2 && !ft_strcmp(argv[1], "-") && ft_getenv("OLDPWD", envp))
		ft_strcpy(path, ft_getenv("OLDPWD", envp));
	else if (argc == 2)
		get_absolute_path_to_buf(argv[1], envp, path);
	else if (ft_getenv("HOME", envp))
		ft_strcpy(path, ft_getenv("HOME", envp));
	else
	{
		err_builtin(E_HOME_NOT_SET, argv[0], NULL);
		return ;
//		return (err_builtin(E_HOME_NOT_SET, argv[0], NULL));
	}
	if (is_valid_folder(path, "cd") != 0)
		return ;
//		return (-1);
	getcwd(cwd, 1024);
	ft_setenv("OLDPWD", cwd, 1, envp);
	if (chdir(path) == -1)
	{
		err_builtin(E_CD_CHANGE_FAIL, "cd", path);
		return ;
//		return (err_builtin(E_CD_CHANGE_FAIL, "cd", path));
	}
	getcwd(cwd, 1024);
	ft_setenv("PWD", cwd, 1, envp);
//	return (0);
}
