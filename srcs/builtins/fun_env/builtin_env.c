/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 12:21:09 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/22 11:53:42 by hlaineka         ###   ########.fr       */
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

int	execute_env(char **argv, char **envp, char *altpath, int options)
{
	char	path[1024];
	int		ret;

	if (argv[0])
	{
		if (options & ENV_P_FLAG)
			ret = find_path(argv[0], altpath, path);
		else
		{
			if (!ft_getenv("PATH", envp))
				return (err_builtin(E_ENV_PATH_NOT_SET, "env", NULL));
			ret = find_path(argv[0], ft_getenv("PATH", envp), path);
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
	char	**argv;
	char	**envp;

	argc = ((t_process *)proc)->argc;
	argv = ((t_process *)proc)->argv;
	envp = ((t_process *)proc)->envp;
	g_pid = fork();
	if (g_pid < 0)
		return ((void)err_builtin(E_FORK, argv[0], NULL));
	else if (g_pid == 0)
		execute_env_child(argc, argv, envp);
	else
		wait(NULL);
	g_pid = 0;
}
