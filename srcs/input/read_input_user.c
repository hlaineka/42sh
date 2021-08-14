/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:34:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/08/14 13:12:16 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"
#include "init.h"
#include "job_control.h"

void	init_input_tty(t_input *input, int prompt_mode)
{
	ft_bzero(input->ls, input->ls_size);
	ft_bzero(input->rrs, input->rrs_size);
	get_pos(&input->start_row, &input->start_col);
	input->prompt_length = print_prompt(prompt_mode);
	get_pos(&input->prompt_row, &input->prompt_col);
	input->cursor_row = input->prompt_row;
	input->cursor_col = input->prompt_col;
//	input->hist_cur = input->last_comm;
	input->hist_i = 0;
}

static void	react_to_keypress(int ret, char **str, t_input *input, t_term *term)
{
	int		len;

	if (ret == -1)
	{
		term->last_return = 1;
		*str = ft_strnew(3);
		if (input->input_mode == HEREDOC_MODE)
			*str[0] = 4;
		ft_strcat(*str, "\n");
	}
	if (ret > 0)
	{
		len = ft_strlen(input->ls) + ft_strlen(input->rrs) + 2;
		*str = ft_memalloc(sizeof(char) * len);
		if (!(*str))
			err_fatal(ERR_MALLOC, NULL, term);
		end_keypress(input, term);
		ft_strcat(*str, input->ls);
		ft_strncat(*str, "\n", 1);
	}
}

char	*read_input_tty(int prompt_mode, t_input *input, t_term *term)
{
	char	read_chars[1024];
	char	*str;
	int		ret;

	init_input_tty(input, prompt_mode);
	if (term->intern_variables->flag_script)
	{
		if (term->intern_variables->script_fd == -1)
		{
			term->intern_variables->script_fd = open(term->intern_variables->script_file, O_RDONLY);
		}
		if (get_next_line(term->intern_variables->script_fd, &str) == 0)
		{
			close(term->intern_variables->script_fd);
			str = ft_strdup("exit");
		}
		ft_printf("%s\n\r", str);
		return (str);
	}
	while (1)
	{
		ft_bzero(read_chars, 1024);
		if (read(STDIN_FILENO, read_chars, 1024) == -1)
			err_fatal(ERR_READ, NULL, term);
		ret = shell_keypress(read_chars, input, term);
		if (ret != 0)
		{
			react_to_keypress(ret, &str, input, term);
			break ;
		}
	}
	ft_putstr("\n\r");
	return (str);
}

static char	*get_input_tty(t_term *term, t_input *input)
{
	int		quote;
	int		len;
	char	*temp;
	char	*temp2;

	input->input_temp = &temp;
	input->quote = &quote;
	quote = PROMPT_START;
	while (quote)
	{
		if (quote == PROMPT_START)
			quote = PROMPT_NORMAL;
		temp = read_input_tty(quote, input, term);
		len = ft_strlen(*input->ret_str);
		if (!(*input->ret_str))
			temp2 = ft_strdup(temp);
		else
			temp2 = ft_strjoin(*input->ret_str, temp);
		free(*input->ret_str);
		free(temp);
		*input->ret_str = temp2;
		temp = *input->ret_str + len;
		quote = ft_is_quote_open(quote, temp);
	}
	return (*input->ret_str);
}

char	*get_input(int argc, char **argv, t_term *term, t_input *input)
{
	char	*str;
	int		quote;

	str = NULL;
	input->ret_str = &str;
	signals_to_ignore();
	if (term->intern_variables->flag_rawmode || (argc == 1
		|| (argc == 3 && ft_strequ(argv[1], "script"))))
	{
		set_signal_input();
		do_job_notification(term->jobs, term);
//		pre_prompt_jobs_check(term);
		enable_raw_mode(term);
		str = get_input_tty(term, input);
//		input->history = command_to_history(input, str);
//		if (!input->history)
		if (command_to_history(str, term))
			err_fatal(ERR_MALLOC, NULL, term);
		disable_raw_mode_continue(term);
	}
	else
	{
		quote = 0;
		get_next_line(STDIN_FILENO, &str);
		quote = ft_is_quote_open(quote, str);
		while (quote)
		{
			get_next_line(STDIN_FILENO, &str);
			quote = ft_is_quote_open(quote, str);
		}
	}
	(void)argv;
	return (str);
}
