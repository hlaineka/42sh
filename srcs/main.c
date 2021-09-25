/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:56:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/25 16:10:14 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "structs_21.h"
#include "parser.h"
#include "ft_signal.h"
#include "execution.h"
#include "init.h"
#include "autotest.h"

int	prompt_cycle(char **argv, t_term *term, t_input *input)
{
	char		*input_str;
	t_node		*root;

	input_str = get_input(1, argv, term, input);
//	if (!ft_strcmp(input_str, "exit\n"))
//	{
//		free(input_str);
//		return (1);
//	}
	root = parser(input_str, term);
	execute(root, term);
//	free_jobs(term);
	int	i;

	i = 1;
	return (0);
}

void	autotest(t_term *term)
{
	char		*input_str;
	t_node		*root;
	int			i;
	char		c;

	i = 0;
	while (g_autotest[i])
	{
		input_str = ft_strdup(g_autotest[i]);
//		if (!ft_strcmp(input_str, "exit\n"))
//		{
//			free(input_str);
//			return ;
//		}
		root = parser(input_str, term);
		execute(root, term);
		free_jobs(term);
		i++;
	}
	ft_printf("press enter to exit: ");
	read(term->fd_stdin, &c, 1);
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
	if (argc == 2 && ft_strequ(argv[1], "autotest"))
		autotest(&term);
	else
	{
		while (exit_value == 0)
			exit_value = prompt_cycle(argv, &term, &input);
	}
	if (term.intern_variables->flag_rawmode)
		disable_raw_mode(&term);
	exit (0);
	return (0);
}
