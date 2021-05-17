/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 22:25:58 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/17 11:50:11 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include "init.h"

void	init_input(t_input *input)
{
	ft_bzero(input, sizeof(t_input));
	input->ls = ft_memalloc(sizeof(char) * 2048);
	if (!input->ls)
		exit(1);
	input->rrs = ft_memalloc(sizeof(char) * 2048);
	if (!input->rrs)
	{
		free(input->ls);
		exit(1);
	}
	input->clipboard = ft_memalloc(sizeof(char) * 2048);
	if (!input->clipboard)
	{
		free(input->ls);
		free(input->rrs);
		exit(1);
	}
	input->history = ft_clstnew(NULL, 0);
	if (!input->history)
		exit(1);
	input->last_comm = input->history;
	input->ls_size = 2048;
	input->rrs_size = 2048;
	input->clipboard_size = 2048;
}

static void	init_term_values(t_term *term, char *buffer)
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
	term->bl_string = tgetstr("bl", &buffer);
	term->nrows = tgetnum("li");
	term->ncolumns = tgetnum("co");
	term->fd_stdin = dup2(STDIN_FILENO, 20);
	term->fd_stdout = dup2(STDOUT_FILENO, 21);
	term->fd_stderr = dup2(STDERR_FILENO, 22);
	term->heredoc_fd = -1;
}

void	init_term(t_term *term)
{
	int		success;
	char	*buffer;

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
	term->buffer = ft_memalloc(sizeof(char) * 2048);
	if (!term->buffer)
		err_fatal(ERR_MALLOC, NULL, term);
	buffer = term->buffer;
	init_term_values(term, buffer);
}

void	init_flags(t_term *term, char **argv)
{
	term->flag_noclobber = 0;
	if (ft_array_length(argv) == 2 && ft_strequ(argv[1], "debug"))
		term->flag_debug = 1;
}

void	initialize(t_input *input, t_term *term, char **envp, char **argv)
{
	ft_bzero(term, sizeof(t_term));
	init_term(term);
	init_flags(term, argv);
	init_input(input);
	copy_envp(envp, term);
	term->input = input;
	get_termios_modes(term);
	tputs(term->ti_string, 1, ft_putc);
	tputs(tgoto(term->cm_string, 0, 0), 1, ft_putc);
	tputs(term->cd_string, 1, ft_putc);
}
