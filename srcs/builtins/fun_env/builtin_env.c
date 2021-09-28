/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/27 18:02:45 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "builtins.h"
#include <sys/types.h>
#include <sys/wait.h>

/*
** NOTIONS:
** - ENV with -i flag will print info that env has been cleared.
*/

static char	*find_path_env(char **envp)
{
	char	*path;

	path = ft_getenv("PATH", envp);
	if (!path)
		path = ft_getenv("PATH", g_term->intern_variables->intern);
	return (path);
}

int	execute_env(char **argv, char **envp, char *altpath, int options)
{
	char	path[1024];
	char	*env_path;
	int		ret;

	env_path = find_path_env(envp);
	if (argv[0])
	{
		if (options & ENV_P_FLAG)
			ret = find_path(argv[0], altpath, path);
		else
		{
			if (!env_path)
				return (err_builtin(E_ENV_PATH_NOT_SET, "env", NULL));
			ret = find_path(argv[0], env_path, path);
		}
		if (ret < 0)
			return (-1);
		if (ret == 0)
			return (err_builtin(E_NOENT, argv[0], NULL));
		execve(path, argv, envp);
	}
	else
		print_envp(envp);
	return (0);
}

int	get_env_options(char **argv, char **envp, int *options, char *altpath)
{
	int		o;
	int		i;

	i = 1;
	while (argv[i] && argv[i][0] == '-')
	{
		o = env_get_options(argv[i], envp);
		if (o == -1 || (o > 8 && o != 16))
			return (err_builtin(E_INVALID_INPUT, "env", argv[i]));
		else if (o & ENV_P_FLAG)
		{
			ft_strncpy(altpath, argv[++i], 1024);
			*options |= ENV_P_FLAG;
		}
		else if (o & ENV_U_FLAG)
		{
			i++;
			if (!argv[i] || !ft_isalpha(argv[i][0]))
				return (err_builtin(E_ILLEGAL_OPTION, "env", argv[i]));
			ft_unsetenv(argv[i], envp);
		}
		i++;
	}
	return (i);
}

static void	execute_env_child(int argc, char **argv, char **envp)
{
	char	altpath[1024];
	int		options;
	int		i;

	i = 0;
	options = 0;
	i = get_env_options(argv, envp, &options, altpath);
	if (i < 0)
		exit(-1);
	i = get_setenvs(argc, argv, envp, i);
	if (i < 0)
		exit(-1);
	exit(execute_env(argv + i, envp, altpath, options));
}

void	builtin_env(void *proc)
{
	int		argc;
	int		status;
	char	**argv;
	char	**envp;

	status = 0;
	argc = ((t_process *)proc)->argc;
	argv = ((t_process *)proc)->argv;
	envp = ((t_process *)proc)->envp;
	g_pid = fork();
	if (g_pid < 0)
		return ((void)err_builtin(E_FORK, argv[0], NULL));
	else if (g_pid == 0)
		execute_env_child(argc, argv, envp);
	waitpid(g_pid, &status, 0);
	((t_process *)proc)->status = status;
	g_pid = 0;
}
