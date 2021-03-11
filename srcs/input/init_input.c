/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:58 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/09 22:30:48 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

/*
void	interrogate_terminal(t_prog *prog)
{
	char	*buffer;

	if (!(buffer = ft_memalloc(sizeof(char) * 2048)))
		err_fatal(ERR_MALLOC, NULL, prog);
	prog->cl_string = tgetstr("cl", &buffer);
	prog->cm_string = tgetstr("cm", &buffer);
	prog->cd_string = tgetstr("cd", &buffer);
	prog->height = tgetnum("li");
	prog->width = tgetnum("co");
	prog->so_string = tgetstr("so", &buffer);
	prog->se_string = tgetstr("se", &buffer);
	prog->mr_string = tgetstr("mr", &buffer);
	prog->me_string = tgetstr("me", &buffer);
	prog->us_string = tgetstr("us", &buffer);
	prog->ue_string = tgetstr("ue", &buffer);
	prog->vi_string = tgetstr("vi", &buffer);
	prog->ve_string = tgetstr("ve", &buffer);
	prog->ti_string = tgetstr("ti", &buffer);
	prog->te_string = tgetstr("te", &buffer);
}

void	init_terminal_data(t_prog *prog)
{
	int		success;

	ft_bzero(prog, sizeof(t_prog));
	g_prog = prog;
	prog->termtype = getenv("TERM");
	if (!isatty(1))
		prog->fd = open(ttyname(ttyslot()), O_RDWR);
	else
		prog->fd = STDOUT_FILENO;
	if (!prog->termtype)
		err_quit(ERR_TERMTYPE_NOT_SET, NULL);
	success = tgetent(prog->term_buffer, prog->termtype);
	if (success < 0)
		err_quit(ERR_TERMCAPS_NO_ACCESS, NULL);
	if (success == 0)
		err_quit(ERR_TERMTYPE_NOT_FOUND, prog->termtype);
}
*/

void			init_input(t_input *input)
{
	ft_bzero(input, sizeof(t_input));
	if (!(input->ls = ft_memalloc(sizeof(char) * 2048)))
		exit(1);
	if (!(input->rrs = ft_memalloc(sizeof(char) * 2048)))
	{
		free(input->ls);
		exit(1);
	}
}
