/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dless.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:45:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/01 12:11:02 by hlaineka         ###   ########.fr       */
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

t_job	*heredoc_pipe_start(t_job *job, t_term *term, t_job *new)
{
	int			rpipe[2];
	
	job->next = term->jobs;
	term->jobs = job;
	pipe(rpipe);
	new->first_process->pid = fork_and_chain_pipes(NULL, rpipe);
	if (new->first_process->pid == 0)
	{
		simple_command(new->first_process);
		exit(new->first_process->status);
	}
	close(job->fd_stdout);
	close(job->fd_stdin);
	job->fd_stdin = rpipe[0];
	job->fd_stdout = rpipe[1];
	return (job);
}

static char	**strarr_add(char **argv, char *command)
{
	int		i;

	i = 0;
	while (argv[i])
		i++;
	argv[i] = ft_strdup(command);
	return(argv);
}

t_job	*token_dless(t_job *job, t_term *term, t_node *current)
{
	char		*delimiter;
	char		*output;
	t_job		*returnable;
	t_job		*new;

	if (job)
		return (NULL);
	output = NULL;
	returnable = NULL;
	delimiter = get_filename(current);  
	delimiter = ft_strjoin_all(delimiter, "\n", 1);
	output = get_input_heredoc(delimiter, term->here_input, term);
	new = init_job(term);
	strarr_add(new->first_process->argv, "echo");
	strarr_add(new->first_process->argv, output);
	if (current->left)
		returnable = heredoc_pipe_start(new, term, new);
	if (current->right)
	{
		returnable = pipe_middle(returnable, term, current->left);
		returnable = pipe_end(returnable, term, current->right);
	}
	if (!current->right && current->left)
		returnable = pipe_end(returnable, term, current->left);
	else
	{
		returnable = new;
		returnable->next = term->jobs;
		term->jobs = returnable;
		simple_command(returnable->first_process);
	}
	ft_memdel((void**)&output);
	ft_memdel((void**)&delimiter);
	return (returnable);
}
