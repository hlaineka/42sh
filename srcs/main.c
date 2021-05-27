/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:56:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/27 16:41:56 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "structs_21.h"
#include "parser.h"
#include "ft_signal.h"
#include "execution.h"
#include "init.h"

int	prompt_cycle(char **argv, t_term *term, t_input *input)
{
	char		*input_str;
	t_node		*root;

	input_str = get_input(1, argv, term, input);
	if (!ft_strcmp(input_str, "exit\n"))
	{
		free(input_str);
		return (1);
	}
	root = parser(input_str, term);
	execute(root, term);
	free_jobs(term);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	t_term		term;
	t_input		input;
	t_input		here_input;
	int			exit_value;

	g_term = &term;
	g_input = &input;
	start_signal();
	initialize(&input, &term, envp, argv);
	init_input(&here_input);
	term.here_input = &here_input;
	exit_value = 0;
	while (exit_value == 0)
		exit_value = prompt_cycle(argv, &term, &input);
	(void)argc;
	(void)argv;
	(void)envp;
	disable_raw_mode(&term);
	exit (0);
	return (0);
}
