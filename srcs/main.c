/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:56:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/30 10:51:00 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "structs_21.h"
#include "parser.h"
#include "ft_signal.h"
#include "execution.h"

int		main(int argc, char **argv, char **envp)
{
	t_term		term;
	t_input		input;
	t_input		here_input;
	char		*input_str;
	//t_job		*next_job;

	//next_job = NULL;
	g_term = &term;
	g_input = &input;
	start_signal(); //signals not done;
	initialize(&input, &term, envp, argv);
	init_input(&here_input);
	term.here_input = &here_input;
//	tputs(tgoto(term.cm_string, 0, 0), 1, ft_putc);
//	tputs(term.cd_string, 1, ft_putc);

//poista t'st'

	//builtin_env(argc - 1, argv + 1, term.envp);

/// t'nne

	while (1)
	{
		input_str = get_input(1, argv, &term, &input); // not done, error check?
//		ft_putstr_input(input_str, &input, &term);
//		ft_printf_fd(STDOUT_FILENO, "\n\r%s\n\r", input_str);
//		ft_printf_fd(STDOUT_FILENO, "%s\n", input_str);
		if (!ft_strcmp(input_str, "exit\n"))
		{
			break;
		}
		parser(input_str, &term);
		//execute_jobs(next_job, &term);

		free(input_str);
		free_jobs(term.jobs);
		//free_tree
//		break;
// input_str to lexer
// token to scanner
	}
	(void)argc;
	(void)argv;
	(void)envp;
	disable_raw_mode(&term);
	ft_putendl(input_str);
	exit (0);
	return (0);
}
