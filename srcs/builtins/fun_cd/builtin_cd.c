/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:22:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/26 09:57:07 by hhuhtane         ###   ########.fr       */
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


static int	cd_get_option(int *option, t_process *p, int argc)
{
	int			i;
	int			j;

	i = 1;
	while (i < argc && p->argv[i][0] == '-')
	{
		j = 1;
		while (p->argv[i][j])
		{
			if (p->argv[i][j] == 'L')
				*option = 1 << L_FLAG;
			else if (p->argv[i][j] == 'P')
				*option = 1 << P_FLAG;
			else
			{
				p->status = err_builtin(E_ILLEGAL_OPTION, "cd", NULL);
				return (-1);
			}
			j++;
		}
		i++;
	}
	return (i);
}

/*
static int	cd_get_option_and_dir(char *path, int *option, t_proc *p, int argc)
{
	int		i;
	char	*home;

	i = cd_get_option(option, p, argc);
	home = ft_getenv("HOME", p->envp);
	if (i == -1)
		return (-1);
	if (i == argc && !home)
	{
		p->status = err_builtin(E_HOME_NOT_SET, p->argv[0], NULL);
		return (-1);
	}
	if (i == argc && home)
	{
		ft_strcpy(path, ft_getenv("HOME", p->envp));
		return (4);
	}
	if (argc > i + 1)
	{
		p->status = err_builtin(E_TOO_MANY_ARGS, p->argv[0], NULL);
		return (-1);
	}
	ft_strcpy(path, p->argv[i]);
	return (i);
}
*/

/*
void	builtin_cd_two(void *proc)
{
	t_process	*p;
	char		path[1024];
	char		curpath[1024];
	int			options;

	p = proc;
	if (cd_get_option_and_dir(path, &options, p, p->argc) == -1)
		return ;
	if (is_absolute_path(path))
		ft_strcpy(curpath, path);
	else
	{
		ft_s
	}
	get_absolute_path_to_buf(path, p->envp, curpath);
}
*/

void	builtin_cd(void *proc)
{
	t_process	*p;
	char		path[1024];
	int			argc;
	int			option;
	int			i;

	p = proc;
	argc = ((t_process *)proc)->argc;
	i = cd_get_option(&option, p, argc);

	if (argc > i + 1)
		p->status = err_builtin(E_TOO_MANY_ARGS, p->argv[0], NULL);
	else if (argc == i + 1 && !ft_strcmp(p->argv[i], "-")
		&& ft_getenv("OLDPWD", p->envp))
		ft_strcpy(path, ft_getenv("OLDPWD", p->envp));
	else if (argc == i + 1)
		get_absolute_path_to_buf(p->argv[i], p->envp, path);
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
	if (option == 1 << P_FLAG)
		change_folder_and_save_pwds(proc, path);
	else
		cd_l_flag(path, p, g_term);
}
