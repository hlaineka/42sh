/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 12:30:39 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/02 12:38:53 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "builtins.h"
#include <sys/types.h>
#include <sys/wait.h>

void	clear_envp(char **envp)
{
	int		i;

	i = 0;
	while (envp && envp[i])
	{
		free(envp[i]);
		envp[i] = NULL;
		i++;
	}
}

void	print_envp(char **envp)
{
	int		i;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
}

int	env_get_options(char *flags, char **envp)
{
	int		i;
	int		options;

	i = 1;
	options = 0;
	while (flags[i])
	{
		if (flags[i] == 'i')
		{
			clear_envp(envp);
		}
		else if (flags[i] == 'P')
			options |= ENV_P_FLAG;
		else if (flags[i] == 'u')
			options |= ENV_U_FLAG;
		else
			return (-1);
		i++;
	}
	return (options);
}

int	get_setenvs(int argc, char **argv, char **envp, int i)
{
	char	*ptr;

	while (i < argc)
	{
		ptr = ft_strchr(argv[i], '=');
		if (!ptr)
			break ;
		*ptr = '\0';
		if (ft_setenv(argv[i], ++ptr, 1, envp) < 0)
			return (-1);
		i++;
	}
	return (i);
}
