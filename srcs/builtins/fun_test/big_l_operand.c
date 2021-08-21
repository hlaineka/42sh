/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_l_operand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/21 21:50:26 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/07/22 17:39:12 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

/*
** -L  pathname
**    True if pathname resolves to a file that exists and is a symbolic
**    link. False if pathname cannot be resolved, or if pathname resolves
**    to a file that exists but is not a symbolic link. If the final
**    component of pathname is a symlink, that symlink is not followed.
*/

void	big_l_operand(void *proc)
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
	if (lstat(p->argv[2], &buf) == -1)
		return ;
	if ((buf.st_mode & S_IFMT) != S_IFLNK)
		return ;
	p->status = 0;
}
