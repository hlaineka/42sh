/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_dless.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:45:44 by hlaineka          #+#    #+#             */
/*   Updated: 2021/05/01 10:56:29 by hlaineka         ###   ########.fr       */
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

t_job	*heredoc_pipe_start(t_job *job, t_term *term, t_process *new)
{
	int			rpipe[2];
	
	job->next = term->jobs;
	term->jobs = job;
	new->next = job->first_process;
	job->first_process = new;
	pipe(rpipe);
	new->pid = fork_and_chain_pipes(NULL, rpipe);
	if (new->pid == 0)
	{
		simple_command(new);
		exit(new->status);
	}
	close(job->fd_stdout);
	close(job->fd_stdin);
	job->fd_stdin = rpipe[0];
	job->fd_stdout = rpipe[1];
	return (job);
}

t_job	*heredoc_pipe_end(t_job *job, t_term *term)
{
	t_process	*temp_process;
	int			lpipe[2];

	temp_process = job->first_process->next;
	lpipe[0] = job->fd_stdin;
	lpipe[1] = job->fd_stdout;
	temp_process->pid = fork_and_chain_pipes(lpipe, NULL);
	if (temp_process->pid == 0)
	{
		dup2(term->fd_stdout, STDOUT_FILENO);
			simple_command(temp_process);
			exit(temp_process->status);
		exit(1);
	}
	close(lpipe[0]);
	close(lpipe[1]);
	waitpid(temp_process->pid, &temp_process->status, 0);
	dup2(term->fd_stdout, STDOUT_FILENO);
	dup2(term->fd_stdin, STDIN_FILENO);
	dup2(term->fd_stderr, STDERR_FILENO);
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
	t_process	*new;

	output = NULL;
	returnable = NULL;
	if (current->left)
		returnable = tree_traversal(job, current->left, term);
	delimiter = get_filename(current);  
	delimiter = ft_strjoin_frees1(delimiter, "\n");
	output = get_input_heredoc(delimiter, term->here_input, term);
	new = init_process(term);
	strarr_add(new->argv, "echo");
	strarr_add(new->argv, output);
	if (returnable)
	{
		returnable = heredoc_pipe_start(returnable, term, new);
		returnable = heredoc_pipe_end(returnable, term);
	}
	else
	{
		returnable = init_job(term);
		new->next = returnable->first_process;
		returnable->first_process = new;
		simple_command(new);
	}
	ft_memdel((void**)&output);
	return (returnable);
}
