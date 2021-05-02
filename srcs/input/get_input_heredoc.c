/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:48:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/05/02 11:34:13 by hhuhtane         ###   ########.fr       */
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

char	*get_input_heredoc(char *eof, t_input *input, t_term *term)
{
	char	*ret;
	char	*temp;
	char	*temp2;
	int		prompt;

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
	disable_raw_mode_continue(term);
	input->heredoc = 0;
	signals_to_default();
	return (ret);
}
