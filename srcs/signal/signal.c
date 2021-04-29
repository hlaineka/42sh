/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:00:31 by helvi             #+#    #+#             */
/*   Updated: 2021/04/29 18:13:24 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
//#include "ft_debug.h"
#include "libft.h"

void	signwinch_handler(int signo)
{
	if (signo == SIGWINCH)
	{
		//reset_screen(g_term);
		//print_selections(g_term, g_term->first);
	}
}

void	sig_handler(int signo)
{
	//h_disable_rawmode();
	if (signo == SIGCHLD)
		sig_child_handler();
	else
	{
		ft_exit(0);
	}
}

void	sigcont_handler(int signo)
{
	if (signo == SIGCONT)
	{
		//check_tty(g_term);
		if (tcsetattr(g_term->fd_stdout, TCSAFLUSH, &g_term->orig_termios) == -1)
			die("tcsetattr");
		//tputs(g_term->ti_string, g_term->nrows, &ft_putc);
		//tputs(tgoto(g_term->cm_string, 0, 0), g_term->nrows, &ft_putc);
	}
}

void	sigtstp_handler(int signo)
{
	if (signo == SIGTSTP)
	{
		//h_disable_rawmode();
		signal(SIGTSTP, SIG_DFL);
		ioctl(STDERR_FILENO, TIOCSTI, "\x1A");
		//tputs(g_term->te_string, g_term->nrows, &ft_putc);
	}
}

void	start_signal(void)
{
	if ((signal(SIGWINCH, signwinch_handler) == SIG_ERR) ||
		(signal(SIGTSTP, sigtstp_handler) == SIG_ERR) ||
		(signal(SIGCONT, sigcont_handler) == SIG_ERR) ||
		(signal(SIGINT, sig_handler) == SIG_ERR) ||
		(signal(SIGQUIT, sig_handler) == SIG_ERR) ||
		(signal(SIGHUP, sig_handler) == SIG_ERR) ||
		(signal(SIGPIPE, sig_handler) == SIG_ERR) ||
		(signal(SIGALRM, sig_handler) == SIG_ERR) ||
		(signal(SIGXCPU, sig_handler) == SIG_ERR) ||
		(signal(SIGXFSZ, sig_handler) == SIG_ERR) ||
		(signal(SIGVTALRM, sig_handler) == SIG_ERR) ||
		(signal(SIGPROF, sig_handler) == SIG_ERR) ||
		(signal(SIGBUS, sig_handler) == SIG_ERR) ||
		(signal(SIGILL, sig_handler) == SIG_ERR) ||
		(signal(SIGABRT, sig_handler) == SIG_ERR) ||
		(signal(SIGIOT, sig_handler) == SIG_ERR) ||
		(signal(SIGTRAP, sig_handler) == SIG_ERR) ||
		(signal(SIGSYS, sig_handler) == SIG_ERR) ||
		(signal(SIGSEGV, sig_handler) == SIG_ERR))
		//(signal(SIGCHLD, sig_handler) == SIG_ERR))
		ft_exit(0);
}
