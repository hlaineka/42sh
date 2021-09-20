/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 12:00:45 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static const char	*g_test_operands_single[] = {
	"-b",
	"-c",
	"-d",
	"-e",
	"-f",
	"-g",
	"-L",
	"-p",
	"-r",
	"-S",
	"-s",
	"-u",
	"-w",
	"-x",
	"-z",
	"!",
	NULL,
	"=",
	"!=",
	"-eq",
	"-ne",
	"-gt",
	"-ge",
	"-lt",
	"-le",
	NULL
};

static const t_fp	g_test_first_fps[] = {
	&b_operand,
	&c_operand,
	&d_operand,
	&e_operand,
	&f_operand,
	&g_operand,
	&big_l_operand,
	&p_operand,
	&r_operand,
	&big_s_operand,
	&s_operand,
	&u_operand,
	&w_operand,
	&x_operand,
	&z_operand,
	&bang_operand,
	NULL,
	&identical_operand,
	&notidentical_operand,
	&eq_operand,
	&ne_operand,
	&gt_operand,
	&ge_operand,
	&lt_operand,
	&le_operand,
	NULL
};

static void	comparison_funs(t_process *p, int i)
{
	if (!p->argv[2])
	{
		p->status = 2;
		return ;
	}
	while (g_test_operands_single[i])
	{
		if (!ft_strcmp(p->argv[2], g_test_operands_single[i]))
			return (g_test_first_fps[i](p));
		i++;
	}
	p->status = 2;
}

void	builtin_test(void *proc)
{
	t_process	*process;
	int			i;
	char		**argv;

	process = proc;
	argv = process->argv;
	i = 0;
	if (process->argc == 2)
	{
		if (ft_strequ(argv[1], ""))
			process->status = 1;
		return ;
	}
	process->status = 1;
	if (process->argc == 1)
		return ;
	while (g_test_operands_single[i])
	{
		if (!ft_strcmp(argv[1], g_test_operands_single[i]))
			return (g_test_first_fps[i](process));
		i++;
	}
	if (process->argc > 4)
		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
	comparison_funs(process, ++i);
}
