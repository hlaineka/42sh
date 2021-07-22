/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_operand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:50:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 15:33:47 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** -w  pathname
**    True if pathname resolves to a file that exists and for which
**    permission to write to the file will be granted, as defined in File
**    Read, Write, and Creation. False if pathname cannot be resolved, or
**    if pathname resolves to a file for which permission to write to the
**    file will not be granted.
*/

void	x_operand(void *proc)
{
	t_process	*p;
	t_stat		buf;

	p = proc;
	p->status = 1;
	if (p->argc > 4)
		return ((void)err_builtin(E_TOO_MANY_ARGS, "test", NULL));
	if (p->argc > 3)
		return ((void)err_builtin(E_BIN_OP_EXP, "test", p->argv[3]));
	if (access(p->argv[2], F_OK))
		return ;
	if (stat(p->argv[2], &buf) == -1)
		return ;
	if (!(buf.st_mode & S_IXUSR))
		return ;
	p->status = 0;	// todo check if this is enough?
}
