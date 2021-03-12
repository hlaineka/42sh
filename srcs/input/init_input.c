/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:58 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/12 18:59:39 by hhuhtane         ###   ########.fr       */
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
	input->ls_size = 2048;
	input->rrs_size = 2048;
}

void			init_term(t_term *term)
{
	int		success;
	char	*buffer;

	ft_bzero(term, sizeof(t_term));
	term->termtype = getenv("TERM");
	if (!isatty(1))
		term->fd_stdout = open(ttyname(ttyslot()), O_RDWR);
	else
		term->fd_stdout = STDOUT_FILENO;
	if (!term->termtype)
		err_quit(ERR_TERMTYPE_NOT_SET, NULL);
	success = tgetent(term->term_buffer, term->termtype);
	if (success < 0)
		err_quit(ERR_TERMCAPS_NO_ACCESS, NULL);
	if (success == 0)
		err_quit(ERR_TERMTYPE_NOT_FOUND, term->termtype);

	if (!(term->buffer = ft_memalloc(sizeof(char) * 2048)))
		err_fatal(ERR_MALLOC, NULL, term);
	buffer = term->buffer;

	term->ti_string = tgetstr("ti", &buffer);
	term->te_string = tgetstr("te", &buffer);
	term->cl_string = tgetstr("cl", &buffer);
	term->cd_string = tgetstr("cd", &buffer);
	term->ce_string = tgetstr("ce", &buffer);
	term->cm_string = tgetstr("cm", &buffer);

	term->nrows = tgetnum("li");
	term->ncolumns = tgetnum("co");

	term->fd_stdin = STDIN_FILENO;
	term->fd_stdout = STDOUT_FILENO; // change to terminal output?
	term->fd_stderr = STDERR_FILENO;
/*
	term->so_string = tgetstr("so", &buffer);
	term->se_string = tgetstr("se", &buffer);
	term->mr_string = tgetstr("mr", &buffer);
	term->me_string = tgetstr("me", &buffer);
	term->us_string = tgetstr("us", &buffer);
	term->ue_string = tgetstr("ue", &buffer);
	term->vi_string = tgetstr("vi", &buffer);
	term->ve_string = tgetstr("ve", &buffer);
*/

	
}

void			initialize(t_input *input, t_term *term)
{
	init_term(term);
	init_input(input);
	enable_raw_mode(term);
	tputs(term->ti_string, 1, ft_putc);
}
