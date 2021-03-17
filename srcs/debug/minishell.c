/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 13:37:18 by hlaineka          #+#    #+#             */
/*   Updated: 2021/03/16 17:04:26 by helvi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_debug.h"
#include "parser.h"

/*
** Prints the prompt (in this shell "$>") reads the input throug lexer()
** adds the command to the info with add_command() and starts scanner()
** to analyse and execute the command.
*/

void	prompt(t_editor *info)
{
	char		*command;

	command = NULL;
	while (!command || !ft_strequ(command, "exit"))
	{
		ft_free(command);
		ft_putstr("$>");
		command = input(info);
		ft_printf("\n");
		if (command)
		{
			add_command(command, info);
			parser(command);
		}
	}
}

/*
** starts the minishell. First allocates and initiates the t_editor pointer,
** that saves most of the data used by the shell. Enables rawmode, clears the
** screen and start the shell by calling on the function prompt.
*/

int		main(int argc, char **argv, char **envp)
{
	t_editor	*info;

	if (argc != 1 || argv[0][0] != '.')
		return (0);
	info = (t_editor*)malloc(sizeof(t_editor));
	info->command_buf = NULL;
	info->print_buf = NULL;
	info->cursorshift = 0;
	info->envp_pointer = ft_strarr_copy(envp);
	enable_rawmode(info);
	check_window_size(info);
	helvi_clear_screen();
	prompt(info);
	ft_exit(0);
}
