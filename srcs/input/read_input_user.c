/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:34:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/25 18:35:30 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

void			init_input_tty(t_input *input, int prompt_mode)
{
	ft_bzero(input->ls, input->ls_size);
	ft_bzero(input->rrs, input->rrs_size);
	get_pos(&input->start_row, &input->start_col);
	input->prompt_length = print_prompt(prompt_mode);
	get_pos(&input->prompt_row, &input->prompt_col);
	input->cursor_row = input->prompt_row;
	input->cursor_col = input->prompt_col;
	input->hist_cur = input->last_comm;
}

char			*read_input_tty(int prompt_mode, t_input *input, t_term *term)
{
	char	read_chars[1024];
	char	*str;
	int		len;

	init_input_tty(input, prompt_mode);
	while (1)
	{
		ft_bzero(read_chars, 1024);
		if (read(STDIN_FILENO, read_chars, 1024) == -1)
			err_fatal(ERR_READ, NULL, term);
		if (shell_keypress(read_chars, input, term))
		{
			len = ft_strlen(input->ls) + ft_strlen(input->rrs) + 2;
			if (!(str = ft_memalloc(sizeof(char) * len)))
				err_fatal(ERR_MALLOC, NULL, term);
			end_keypress(input, term);
			tputs(tgoto(term->cm_string, input->prompt_col - 1, input->prompt_row - 1), 1, ft_putc);
			ft_putstr_input(input->ls, input, term);
//			get_pos(&input->cursor_row, &input->cursor_col);
			ft_strcat(str, input->ls);
			ft_strncat(str, "\n", 1);
			ft_putstr_input("\n", input, term);
			break ;
		}
	}
	return (str);
}

char			*get_input(int argc, char **argv, t_term *term, t_input *input)
{
	int		quote;
	int		len;
	char	*str;
	char	*temp;
	char	*temp2;

	str = NULL;
	quote = 0;
	enable_raw_mode(term);
	if (argc == 1)
	{
		str = read_input_tty(PROMPT_NORMAL, input, term);
		temp = str;
		while ((quote = ft_is_quote_open(quote, temp)))
		{
			temp = read_input_tty(quote, input, term);
			len = ft_strlen(str);
			temp2 = ft_strjoin(str, temp); // error check?
			free(str);
			free(temp);
			str = temp2;
			temp = str + len;
		}
		if (!(input->history = command_to_history(input, str)))
			err_fatal(ERR_MALLOC, NULL, term);
	}
	(void)argv;
	disable_raw_mode_continue(term);
	return (str);
}
