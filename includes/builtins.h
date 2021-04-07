/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:11:01 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/07 15:57:00 by hhuhtane         ###   ########.fr       */
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


int		is_builtin(t_process *process);

/*
** CD BUILTIN:
*/
void	builtin_cd(void *proc);
int		find_path(char *file, char *path_env, char *buf);
int		is_absolute_path(char *path);
int		is_valid_folder(char *path);
char	*get_absolute_path_to_buf(char *rel, char **envp, char *buf);

/*
** ENV FUNCTION PROTOTYPES
*/

int		err_builtin(int error_no, char *name, char *arg);

char	*ft_getenv(const char *name, char **envp);
int		ft_setenv(const char *name, const char *val, int over, char **envp);
int		ft_unsetenv(const char *name, char **envp);

int		builtin_unsetenv(int argc, char **argv, char **envp);
int		builtin_setenv(int argc, char **argv, char **envp);
void	builtin_env(void *proc);

#endif
