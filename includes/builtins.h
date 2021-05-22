/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:11:01 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/22 11:47:55 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "typedefs.h"

# define ENV_P_FLAG 1
# define ENV_U_FLAG 2

pid_t	g_pid;

int		is_builtin(t_process *process);

/*
** CD BUILTIN:
*/
void	builtin_cd(void *proc);
int		find_path(char *file, char *path_env, char *buf);
int		is_absolute_path(char *path);
int		is_valid_folder(char *path, char *progname);
char	*get_absolute_path_to_buf(char *rel, char **envp, char *buf);

/*
** ECHO BUILTIN
*/

void	builtin_echo(void *proc);

/*
** ENV FUNCTION PROTOTYPES
*/

int		err_builtin(int error_no, char *name, char *arg);

char	*ft_getenv(const char *name, char **envp);
int		ft_setenv(const char *name, const char *val, int over, char **envp);
int		ft_unsetenv(const char *name, char **envp);

void	builtin_env(void *proc);

/*
** SETENV BUILTIN:
*/

void	builtin_setenv(void *proc);

/*
** UNSETENV BUILTIN:
*/

void	builtin_unsetenv(void *proc);

/*
** ENV BUILTIN:
*/

void	clear_envp(char **envp);
void	print_envp(char **envp);
int		env_get_options(char *flags, char **envp);
int		get_setenvs(int argc, char **argv, char **envp, int i);

#endif
