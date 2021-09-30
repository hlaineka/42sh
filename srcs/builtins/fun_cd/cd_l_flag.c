/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_l_flag.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 19:47:03 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/30 19:34:16 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	create_path_lst(char **folders, t_list *lst)
{
	int		i;
	t_list	*tmp;

	i = 0;
	while (folders[i])
	{
		tmp = ft_lstnew(folders[i], ft_strlen(folders[i]) + 1);
		ft_lstappend(&lst, tmp);
		free(folders[i]);
		i++;
	}
	free(folders);
}

static void	write_curpath_from_lst(char *curpath, t_list *lst)
{
	t_list	*temp;

	if (lst->next == NULL)
		ft_strcat(curpath, "/");
	while (lst->next)
	{
		temp = lst;
		lst = lst->next;
		ft_lstdelone(&temp, &cd_lst_delete);
		ft_strcat(curpath, "/");
		ft_strcat(curpath, lst->content);
	}
	ft_lstdelone(&lst, &cd_lst_delete);
}

static int	set_cwd_and_env(char *curpath, t_process *p)
{
	char	temp[1024];
	char	*pwd;

	pwd = ft_getenv("PWD", g_term->envp);
	if (chdir(curpath) == -1)
	{
		p->status = err_builtin(E_CD_CHANGE_FAIL, "cd", curpath);
		return (p->status);
	}
	if (!pwd)
	{
		getcwd(temp, 1024);
		ft_setenv("OLDPWD", temp, 1, g_term->envp);
	}
	else
		ft_setenv("OLDPWD", pwd, 1, g_term->envp);
	ft_setenv("PWD", curpath, 1, g_term->envp);
	return (0);
}

static void	clean_the_path(char *path, t_process *p)
{
	t_list	*lst;
	char	**folders;
	char	curpath[1024];

	lst = ft_lstnew(NULL, 0);
	ft_bzero(curpath, 1024);
	folders = ft_strsplit(path, '/');
	if (!folders)
	{
		p->status = err_builtin(E_CD_CHANGE_FAIL, "cd", curpath);
		return ;
	}
	create_path_lst(folders, lst);
	cd_remove_dots(lst);
	write_curpath_from_lst(curpath, lst);
	set_cwd_and_env(curpath, p);
}

void	cd_l_flag(char *path, t_process *p, t_term *term)
{
	char	curpath[1024];
	char	*pwd;

	pwd = ft_getenv("PWD", term->envp);
	ft_bzero(curpath, 1024);
	if (path[0] != '/')
	{
		if (pwd)
		{
			if (ft_strcmp(pwd, "/"))
				ft_strcpy(curpath, pwd);
		}
		else
			getcwd(curpath, 1024);
		ft_strcat(curpath, "/");
	}
	ft_strcat(curpath, path);
	clean_the_path(curpath, p);
}
