/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_operand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:50:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 17:39:51 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** -f  pathname
**    True if pathname resolves to a file that exists and is a regular file.
**    False if pathname cannot be resolved, or if pathname resolves to a file
**    that exists but is not a regular file.
*/

void	f_operand(void *proc)
{
	t_process	*p;
	t_stat		buf;

	p = proc;
	p->status = 2;
	if (p->argc > 4)
		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
	if (p->argc > 3)
		return ((void)err_builtin(E_BIN_OP_EXP, "test", p->argv[3]));
	p->status = 1;
	if (access(p->argv[2], F_OK))
		return ;
	if (stat(p->argv[2], &buf) == -1)
		return ;
	if ((buf.st_mode & S_IFMT) != S_IFREG)
		return ;
	p->status = 0;
}
