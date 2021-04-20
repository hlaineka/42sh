/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 21:48:18 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/04/20 22:16:19 by hhuhtane         ###   ########.fr       */
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
	temp = NULL;
	prompt = PROMPT_HEREDOC;
// all signal stuff
	signal(SIGINT, sig_handler_input);
	input->heredoc = 1;

	enable_raw_mode(term);
	while (1)
	{
		temp = read_input_tty(prompt, input, term);
		if (ft_strequ(eof, temp) || ft_strequ("EOF", temp))
		{
			free(temp);
			break ;
		}
		temp2 = ft_strjoin(ret, temp);
		free(ret);
		ret = temp2;
	}
	disable_raw_mode(term);
	input->heredoc = 0;
	return (ret);
}
