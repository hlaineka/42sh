/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 10:00:31 by helvi             #+#    #+#             */
/*   Updated: 2021/06/13 11:38:19 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include "libft.h"

void	signwinch_handler(int signo)
{
	if (signo == SIGWINCH)
	{
	}
}

void	sig_handler(int signo)
{
	ft_printf("sig_handler %i", signo);
	if (signo == SIGCHLD)
		sig_child_handler();
	else
		exit(0);
}

void	sigcont_handler(int signo)
{
	ft_printf("sigcont_handler");
	if (signo == SIGCONT)
	{
		if (tcsetattr(g_term->fd_stderr, TCSAFLUSH, &g_term->orig_termios)
			== -1)
			die("tcsetattr");
	}
}

void	sigtstp_handler(int signo)
{
	(void)signo;
}

void	start_signal(void)
{
	if ((signal(SIGWINCH, signwinch_handler) == SIG_ERR)
		|| (signal(SIGTSTP, sigtstp_handler) == SIG_ERR)
		|| (signal(SIGCONT, sigcont_handler) == SIG_ERR)
		|| (signal(SIGINT, sig_handler) == SIG_ERR)
		|| (signal(SIGQUIT, sig_handler) == SIG_ERR)
		|| (signal(SIGHUP, sig_handler) == SIG_ERR)
		|| (signal(SIGPIPE, sig_handler) == SIG_ERR)
		|| (signal(SIGALRM, sig_handler) == SIG_ERR)
		|| (signal(SIGXCPU, sig_handler) == SIG_ERR)
		|| (signal(SIGXFSZ, sig_handler) == SIG_ERR)
		|| (signal(SIGVTALRM, sig_handler) == SIG_ERR)
		|| (signal(SIGPROF, sig_handler) == SIG_ERR)
		|| (signal(SIGBUS, sig_handler) == SIG_ERR)
		|| (signal(SIGILL, sig_handler) == SIG_ERR)
		|| (signal(SIGABRT, sig_handler) == SIG_ERR)
		|| (signal(SIGIOT, sig_handler) == SIG_ERR)
		|| (signal(SIGTRAP, sig_handler) == SIG_ERR)
		|| (signal(SIGSYS, sig_handler) == SIG_ERR)
		|| (signal(SIGSEGV, sig_handler) == SIG_ERR))
		ft_exit(0);
}
