/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:22:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/08 16:44:25 by hhuhtane         ###   ########.fr       */
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

void	change_folder_and_save_pwds(t_process *proc, char path[])
{
	get_cwd_and_set_env("OLDPWD", proc->envp);
	if (chdir(path) == -1)
	{
		proc->status = err_builtin(E_CD_CHANGE_FAIL, "cd", path);
		return ;
	}
	get_cwd_and_set_env("PWD", proc->envp);
}

void	builtin_cd(void *proc)
{
	t_process	*p;
	char		path[1024];
	int			argc;

	p = proc;
	argc = ((t_process *)proc)->argc;
	if (argc > 2)
		p->status = err_builtin(E_TOO_MANY_ARGS, p->argv[0], NULL);
	else if (argc == 2 && !ft_strcmp(p->argv[1], "-")
		&& ft_getenv("OLDPWD", p->envp))
		ft_strcpy(path, ft_getenv("OLDPWD", p->envp));
	else if (argc == 2)
		get_absolute_path_to_buf(p->argv[1], p->envp, path);
	else if (ft_getenv("HOME", p->envp))
		ft_strcpy(path, ft_getenv("HOME", p->envp));
	else
		p->status = err_builtin(E_HOME_NOT_SET, p->argv[0], NULL);
	if (p->status)
		return ;
	if (is_valid_folder(path, "cd") != 0)
		p->status = 1;
	if (p->status)
		return ;
	change_folder_and_save_pwds(proc, path);
}
