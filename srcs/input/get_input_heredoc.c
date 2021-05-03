/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:48:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/03 17:21:40 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

static void	init_heredoc_reading(char **ret, t_input *input, char **temp)
{
	*temp = NULL;
	*ret = ft_strnew(0);
	input->ret_str = ret;
	input->input_temp = temp;
	input->heredoc = 1;
	set_signal_input();
}

static void	heredoc_change_streams_start(t_term *term, int streams[])
{
	streams[0] = dup(STDIN_FILENO);
	streams[1] = dup(STDOUT_FILENO);
	streams[2] = dup(STDERR_FILENO);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
}

static void	heredoc_change_streams_end(int streams[], t_term *term)
{
	disable_raw_mode_continue(term);
	signals_to_default();
	dup2(streams[0], STDIN_FILENO);
	dup2(streams[1], STDOUT_FILENO);
	dup2(streams[2], STDERR_FILENO);
	close(streams[0]);
	close(streams[1]);
	close(streams[2]);
}

char	*get_input_heredoc(char *eof, t_input *input, t_term *term)
{
	char	*ret;
	char	*temp;
	char	*temp2;
	int		prompt;
	int		streams[3];

	heredoc_change_streams_start(term, streams);
	init_heredoc_reading(&ret, input, &temp);
	enable_raw_mode(term);
	prompt = PROMPT_HEREDOC;
	while (1)
	{
		temp = read_input_tty(prompt, input, term);
		if (ft_strequ(eof, temp) || ft_strequ("EOF\n", temp))
			break ;
		temp2 = ft_strjoin(ret, temp);
		free(ret);
		free(temp);
		ret = temp2;
	}
	free(temp);
	ret[ft_strlen(ret) - 1] = '\0';
	input->heredoc = 0;
	heredoc_change_streams_end(streams, term);
	return (ret);
}
