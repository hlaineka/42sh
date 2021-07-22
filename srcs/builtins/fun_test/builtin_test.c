/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:57:52 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 14:53:28 by hhuhtane         ###   ########.fr       */
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
//	"-S",
//	"-s",
//	"-u",
//	"-w",
//	"-x",
//	"-z",
//	"!",
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
//	&big_s_operand,
//	&s_operand,
//	&u_operand,
//	&w_operand,
//	&x_operand,
//	&z_operand,
//	&bang_operand,
	NULL
};

void	builtin_test(void *proc)
{
//	t_term		*term;
	t_process	*process;
	int			argc;
	int			i;
	char		**argv;

	process = proc;
	argv = process->argv;
	argc = process->argc;
	i = 0;
	if (argc == 1)
	{
		process->status = 1;
		return ;
	}
	while (g_test_operands_single[i])
	{
		if (!ft_strcmp(argv[1], g_test_operands_single[i]))
			return (g_test_first_fps[i](process));
		i++;
	}

	if (argc > 4)
	{
		process->status = 1;
		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
	}
}
