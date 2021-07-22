/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 10:11:01 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 18:31:26 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include <unistd.h>
# include <sys/stat.h>
# include "structs_21.h"
# include "typedefs.h"

# define ENV_P_FLAG 1
# define ENV_U_FLAG 2

# define A_FLAG 0
# define B_FLAG 1
# define C_FLAG 2
# define D_FLAG 3
# define E_FLAG 4
# define F_FLAG 5
# define G_FLAG 6
# define H_FLAG 7
# define I_FLAG 8
# define J_FLAG 9
# define K_FLAG 10
# define L_FLAG 11
# define M_FLAG 12
# define N_FLAG 13
# define O_FLAG 14
# define P_FLAG 15
# define Q_FLAG 16
# define R_FLAG 17
# define S_FLAG 18
# define T_FLAG 19
# define U_FLAG 20
# define V_FLAG 21
# define X_FLAG 22
# define Y_FLAG 23
# define Z_FLAG 24

typedef struct stat		t_stat;

pid_t	g_pid;

int		is_builtin(t_process *process);
int		is_builtin_type(char *cmd);
int		get_argv_options(char **argv, int *options);
int		get_argv_options_next(char **argv, int *options);

int		is_digit_str(char *str);

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


/*
** FG BUILTIN:
*/

void	builtin_fg(void *proc);

/*
** BG BUILTIN:
*/

void	builtin_bg(void *proc);

/*
** JOBS BUILTIN:
*/

void	builtin_jobs(void *proc);
int		print_active_job(t_job *job, int options, t_term *term);

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

void	builtin_env(void *proc);
void	clear_envp(char **envp);
void	print_envp(char **envp);
int		env_get_options(char *flags, char **envp);
int		get_setenvs(int argc, char **argv, char **envp, int i);

/*
** FC BUILTIN:
*/
void	builtin_fc(void *proc);
int		fc_es(t_term *term, t_fc *fc, int options);
int		parse_and_execute(char *cmd, t_term *term);

/*
** TEST BUILTIN:
*/
void	builtin_test(void *proc);
void	b_operand(void *proc);
void	c_operand(void *proc);
void	d_operand(void *proc);
void	e_operand(void *proc);
void	f_operand(void *proc);
void	g_operand(void *proc);
void	big_l_operand(void *proc);
void	p_operand(void *proc);
void	r_operand(void *proc);
void	big_s_operand(void *proc);
void	s_operand(void *proc);
void	u_operand(void *proc);
void	w_operand(void *proc);
void	x_operand(void *proc);
void	z_operand(void *proc);
void	bang_operand(void *proc);
void	identical_operand(void *proc);
void	notidentical_operand(void *proc);
void	eq_operand(void *proc);
void	ne_operand(void *proc);
void	gt_operand(void *proc);
void	ge_operand(void *proc);
void	lt_operand(void *proc);
void	le_operand(void *proc);

#endif
