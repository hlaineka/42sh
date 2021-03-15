/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: helvi <helvi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:56:34 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/15 10:38:05 by helvi            ###   ########.fr       */
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
	t_job		*next_job;

	g_term = &term;
//	signals(); //signals not done;
	initialize(&input, &term);
	tputs(tgoto(term.cm_string, 0, 0), 1, ft_putc);
	tputs(term.cd_string, 1, ft_putc);
	while (1)
	{
		input_str = get_input(argc, argv, &term, &input); // not done, error check?
		next_job = parser(input_str);
		ft_free(next_job);//job leaks
	}

	(void)argc;
	(void)argv;
	(void)envp;
	disable_raw_mode(&term);
	ft_putendl(input_str);
	return (0);
}
