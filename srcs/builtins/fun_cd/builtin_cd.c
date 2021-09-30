/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 14:22:43 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/30 19:44:24 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

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
		if (!ft_strcmp(p->argv[i], "-"))
			return (i);
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

static void	change_folder(char path[], int option, t_process *p)
{
	if (is_valid_folder(path, "cd") != 0)
		p->status = 1;
	if (p->status)
		return ;
	if (option == 1 << P_FLAG)
		change_folder_and_save_pwds(p, path);
	else
		cd_l_flag(path, p, g_term);
}

void	builtin_cd(void *proc)
{
	t_process	*p;
	char		path[1024];
	int			argc;
	int			option;
	int			i;

	p = proc;
	option = 0;
	ft_bzero(path, sizeof(char) * 1024);
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
	change_folder(path, option, p);
}
