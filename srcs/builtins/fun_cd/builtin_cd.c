/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:22:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/02 13:26:58 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

//int	builtin_cd(int argc, char **argv, char **envp)

void	get_cwd_and_set_env(char *set_env, char **envp)
{
	char		cwd[1024];

	getcwd(cwd, 1024);
	ft_setenv(set_env, cwd, 1, envp);
}

void	builtin_cd(void *proc)
{
	char		path[1024];
	int			argc;
	char		**argv;
	char		**envp;

	envp = ((t_process *)proc)->envp;
	argv = ((t_process *)proc)->argv;
	argc = ((t_process *)proc)->argc;
	if (argc > 2)
		return ((void)err_builtin(E_TOO_MANY_ARGS, argv[0], NULL));
	if (argc == 2 && !ft_strcmp(argv[1], "-") && ft_getenv("OLDPWD", envp))
		ft_strcpy(path, ft_getenv("OLDPWD", envp));
	else if (argc == 2)
		get_absolute_path_to_buf(argv[1], envp, path);
	else if (ft_getenv("HOME", envp))
		ft_strcpy(path, ft_getenv("HOME", envp));
	else
		return ((void)err_builtin(E_HOME_NOT_SET, argv[0], NULL));
	if (is_valid_folder(path, "cd") != 0)
		return ;
	get_cwd_and_set_env("OLDPWD", envp);
	if (chdir(path) == -1)
		return ((void)err_builtin(E_CD_CHANGE_FAIL, "cd", path));
	get_cwd_and_set_env("PWD", envp);
}
