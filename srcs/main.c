/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:56:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/15 11:32:03 by helvi            ###   ########.fr       */
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
	start_signal(); //signals not done;
	initialize(&input, &term);
	ft_atexit(&disable_rawmode);
	tputs(tgoto(term.cm_string, 0, 0), 1, ft_putc);
	tputs(term.cd_string, 1, ft_putc);
	while (1)
	{
		input_str = get_input(argc, argv, &term, &input); // not done, error check?
		break;
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
