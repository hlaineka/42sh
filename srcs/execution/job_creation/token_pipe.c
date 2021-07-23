/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/07 16:51:19 by hlaineka          #+#    #+#             */
/*   Updated: 2021/07/20 20:22:39 by hlaineka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include "execution.h"
#include "libft.h"
#include <sys/wait.h>

/*
** Handles the execution and pipe line creation of pipe operator.
** If there is other pipes in the command, traverses the tree
** and then executes the commands.
*/

t_job	*pipe_child(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;

	if (!current->left || (!job && !current->right))
		return (NULL);
	returnable = job;
	if (current->left->operation == tkn_pipe)
		returnable = tree_traversal(returnable, current->left, term);
	else if (!returnable)
		returnable = pipe_start(returnable, term, current->left);
	else if (!current->right)
		returnable = pipe_end(returnable, term, current->left);
	else
		returnable = pipe_middle(returnable, term, current->left);
	if (current->right->operation == tkn_pipe)
		returnable = tree_traversal(returnable, current->right, term);
	else if (current->parent && current->parent->operation == tkn_pipe)
		returnable = pipe_middle(returnable, term, current->right);
	else
		returnable = pipe_end(returnable, term, current->right);
	return (returnable);
}

t_job	*token_pipe(t_job *job, t_term *term, t_node *current)
{
	t_job	*returnable;
	int		pid;
	int		status;

	//fork if job == NULL
	//parent calls setpgid, tcsetpgrp, waitpid, tcsetpgrp
	//child does the tree traversal and starts the other children
	// parent waits for child.
	pid = 0;
	if (job != NULL)
		returnable = pipe_child(job, term, current);
	else
	{
		pid = fork();
		if (pid == 0)
		{
			returnable = pipe_child(job, term, current);
			exit(job->first_process->status);
		}
		else
		{
			returnable = init_job(current);
			returnable->first_process->pid = pid;
			setpgid(pid, 0);
			//tcsetpgrp()
			waitpid(pid, &status, WUNTRACED);
			returnable->first_process->status = status;
			//tcsetpgrp()
		}
	}
	return (returnable);
}
