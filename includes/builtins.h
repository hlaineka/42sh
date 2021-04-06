/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:11:01 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/06 13:45:58 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "typedefs.h"

# define ENV_P_FLAG 1
# define ENV_U_FLAG 2

/*
** termporary error nums
*/

# define ERR_PATH_NOT_SET 123
# define ERR_FILE_NOT_FOUND 124
# define ERR_INVALID_INPUT 134

pid_t	g_pid;

/*
** ENV FUNCTION PROTOTYPES
*/

int		err_builtin(int error_no, char *name, char *arg);
int		find_path(char *file, char *path_env, char *buf);

char	*ft_getenv(const char *name, char **envp);
int		ft_setenv(const char *name, const char *val, int over, char **envp);
int		ft_unsetenv(const char *name, char **envp);

int		builtin_unsetenv(int argc, char **argv, char **envp);
int		builtin_setenv(int argc, char **argv, char **envp);
int		builtin_env(int argc, char **argv, char **envp);

#endif
