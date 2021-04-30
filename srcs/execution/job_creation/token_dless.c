/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dless.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:45:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/04/30 15:01:56 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "input.h"
#include "libft.h"
#include "execution.h"
#include <sys/stat.h>
#include <fcntl.h>

/*
**
*/

char	*ft_strjoin_all(char *str1, char *str2, int mode)
{
	char	*returnable;
	int		i;
	int		w;

	returnable = ft_strnew(ft_strlen(str1) + ft_strlen(str2) + 1);
	i = 0;
	w = 0;
	while (str1 && str1[i])
		returnable[w++] = str1[i++];
	i = 0;
	while (str2 && str2[i])
		returnable[w++] = str2[i++];
	returnable[w] = '\0';
	if (mode == 1 || mode == 3)
		ft_free(str1);
	if (mode == 2 || mode == 3)
		ft_free(str2);
	return (returnable); 
}

t_job	*token_dless(t_job *job, t_term *term, t_node *current)
{
	char	*delimiter;
	int		lpipe[2];
	char	*output;
	t_job	*returnable;

	output = NULL;
	returnable = get_left_job(job, current, term);
	delimiter = get_filename(current);  
	delimiter = ft_strjoin_frees1(delimiter, "\n");
	output = get_input_heredoc(delimiter, term->here_input, term);
	if (returnable)
	{
		pipe(lpipe);
		write(lpipe[1], output, ft_strlen(output));
		dup2(lpipe[0], STDIN_FILENO);
		returnable->first_process->status = simple_command(returnable->first_process);
		close(lpipe[0]);
		close(lpipe[1]);
		dup2(term->fd_stdin, STDIN_FILENO);
	}
	else
	{
		write(STDOUT_FILENO, output, ft_strlen(output));
		write(STDOUT_FILENO, "\n", 1);
	}
	ft_memdel((void**)&output);
	return (returnable);
}
