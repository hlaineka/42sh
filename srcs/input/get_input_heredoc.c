/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:48:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/21 11:37:39 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"


char	*get_input_heredoc(char *eof, t_input *input, t_term *term)
{
	char	*ret;
	char	*temp;
	char	*temp2;
	int		prompt;

	ret = NULL;
	input->ret_str = &ret;
	input->input_temp = &temp;
	temp = NULL;
	prompt = PROMPT_HEREDOC;
// all signal stuff
	signal(SIGINT, sig_handler_input);
	signal(SIGCONT, sig_handler_input);
	signal(SIGTSTP, sig_handler_input);
	signal(SIGTERM, sig_handler_input);
	signal(SIGQUIT, sig_handler_input);
	signal(SIGHUP, sig_handler_input);
	signal(SIGPIPE, sig_handler_input);
	signal(SIGALRM, sig_handler_input);
	input->heredoc = 1;

	enable_raw_mode(term);
	while (1)
	{
		temp = read_input_tty(prompt, input, term);
		if (ft_strequ(eof, temp) || ft_strequ("EOF\n", temp))
		{
			free(temp);
			break ;
		}
		temp2 = ft_strjoin(ret, temp);
		free(ret);
		ret = temp2;
	}
	disable_raw_mode_continue(term);
	input->heredoc = 0;
	signal(SIGINT, SIG_DFL);
	return (ret);
}
