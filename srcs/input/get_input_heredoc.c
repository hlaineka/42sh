/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:48:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/09/14 16:11:26 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"
#include "init.h"

static void	heredoc_change_streams_start(t_term *term, int streams[])
{
	streams[0] = dup(STDIN_FILENO);
	streams[1] = dup(STDOUT_FILENO);
	streams[2] = dup(STDERR_FILENO);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
	enable_raw_mode(term);
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

static char	*get_input_heredoc2(char *eof, t_input *input, t_term *term)
{
	char	*temp;
	char	*temp2;
	int		prompt;

	temp = NULL;
	temp2 = NULL;
	input->input_temp = &temp;
	prompt = PROMPT_HEREDOC;
	while (1)
	{
		temp = read_input_tty(prompt, input, term);
		if (ft_strequ(eof, temp) || (temp[0] == 4 && temp[1] == '\n'))
			break ;
		temp2 = ft_strjoin(*input->ret_str, temp);
		free(*input->ret_str);
		free(temp);
		*input->ret_str = temp2;
	}
	if (temp != NULL)
		ft_memdel((void **)&temp);
	return (*input->ret_str);
}

static int	init_heredoc_input(char **str, char **buf, t_input *input)
{
	*str = ft_strnew(0);
	if (*str == NULL)
		return (1);
	*buf = ft_strnew(0);
	if (*buf == NULL)
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	input->ret_str = str;
	input->input_mode = HEREDOC_MODE;
	signals_to_ignore();
	return (0);
}

char	*get_input_heredoc(char *eof, t_input *input, t_term *term)
{
	char	*str;
	char	*buf;
	int		streams[3];

	if (init_heredoc_input(&str, &buf, input))
		return (NULL);
	if (term->intern_variables->flag_rawmode)
	{
		heredoc_change_streams_start(term, streams);
		str = get_input_heredoc2(eof, input, term);
		free(buf);
		heredoc_change_streams_end(streams, term);
		if (ft_strlen(str) > 0)
			str[ft_strlen(str) - 1] = '\0';
	}
	else
	{
		while (!ft_strequ(eof, buf))
		{
			get_next_line(STDIN_FILENO, &buf);
			str = ft_strjoin_frees1(str, buf);
		}
	}
	input->input_mode = 0;
	return (str);
}
