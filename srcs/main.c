/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:56:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/17 18:31:20 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "structs_21.h"

int		main(int argc, char **argv, char **envp)
{
	t_term		term;
	t_input		input;
	char		*input_str;

	g_term = &term;
//	signals(); //signals not done;
	initialize(&input, &term);
	tputs(tgoto(term.cm_string, 0, 0), 1, ft_putc);
	tputs(term.cd_string, 1, ft_putc);
	while (1)
	{
		input_str = get_input(argc, argv, &term, &input); // not done, error check?
		ft_printf_fd(STDOUT_FILENO, "\n\r%s\n\r", input_str);
		if (!ft_strcmp(input_str, "exit"))
		{
			break;
		}
		free(input_str);
//		break;
// input_str to lexer
// token to scanner

	}

	(void)argc;
	(void)argv;
	(void)envp;
	disable_raw_mode(&term);
	ft_putendl(input_str);
	return (0);
}
