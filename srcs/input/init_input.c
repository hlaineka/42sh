/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:58 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/25 18:39:20 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

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
	if (!(input->clipboard = ft_memalloc(sizeof(char) * 2048)))
	{
		free(input->ls);
		free(input->rrs);
		exit(1);
	}
	if (!(input->history = ft_clstnew(NULL, 0)))
		exit(1); //FIX this
	input->last_comm = input->history;
	input->ls_size = 2048;
	input->rrs_size = 2048;
	input->clipboard_size = 2048;
}

static void		get_termcaps_strings(t_term *term, char *buffer)
{
	term->ti_string = tgetstr("ti", &buffer);
	term->te_string = tgetstr("te", &buffer);
	term->cl_string = tgetstr("cl", &buffer);
	term->cd_string = tgetstr("cd", &buffer);
	term->ce_string = tgetstr("ce", &buffer);
	term->cm_string = tgetstr("cm", &buffer);
	term->le_string = tgetstr("le", &buffer);
	term->nd_string = tgetstr("nd", &buffer);
	term->sc_string = tgetstr("sc", &buffer);
	term->rc_string = tgetstr("rc", &buffer);
	term->dc_string = tgetstr("dc", &buffer);
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
	get_termcaps_strings(term, buffer);
	term->nrows = tgetnum("li");
	term->ncolumns = tgetnum("co");
	term->fd_stdin = STDIN_FILENO;
	term->fd_stdout = STDOUT_FILENO; // change to terminal output?
	term->fd_stderr = STDERR_FILENO;
}

void			initialize(t_input *input, t_term *term)
{
	init_term(term);
	init_input(input);
	term->input = input;
	get_termios_modes(term);
//	enable_raw_mode(term);
	tputs(term->ti_string, 1, ft_putc);
	tputs(tgoto(term->cm_string, 0, 0), 1, ft_putc);
	tputs(term->cd_string, 1, ft_putc);
}
