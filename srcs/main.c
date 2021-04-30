/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:56:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/30 14:25:36 by hlaineka         ###   ########.fr       */
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
	t_node		*root;

	g_term = &term;
	g_input = &input;
	start_signal(); //signals not done;
	initialize(&input, &term, envp, argv);
	init_input(&here_input);
	term.here_input = &here_input;
	while (1)
	{
		input_str = get_input(1, argv, &term, &input); // not done, error check?
		if (!ft_strcmp(input_str, "exit\n"))
		{
			break;
		}
		root = parser(input_str, &term);
		execute(root, &term);
		free(input_str);
		free_jobs(&term);
	}
	(void)argc;
	(void)argv;
	(void)envp;
	disable_raw_mode(&term);
	ft_putendl(input_str);
	exit (0);
	return (0);
}
