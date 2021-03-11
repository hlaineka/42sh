/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:34:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/11 20:44:57 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

/*
static void		err_temp(int errorno, char *message, t_termios orig)
{
	disable_raw_mode(orig);
	if (errorno == ERR_READ)
		ft_printf_fd(2, "Read fail\n")
}

static int		is_special_key(char *rc)
{
	if (rc[0] < 32 || rc[0] == 127) // Is this correct?
		return (1);
	return (0);
}

static void		do_special_keys(char *rc, char *ls, char *rrs, t_prog *prog)
{
	if (rc[0] == KEY_ESC)
	{
		if (rc[1] == 91)
		{

//			if (rc[2] == 65) // UP arrow
//				history_up(); //PSEUDO
//			if (rc[2] == 66) // DOWN arrow
//				history_down; //PSEUDO

			if (rc[2] == 67) // RIGHT arrow
				move_char_from_rrs_to_ls;
			if (rc[2] == 68) // LEFT arrow
				move_char_from_ls_to_rrs;
		}
	}
	else if (rc[0] == 13) // enter
		dostuff();

//	if (rc == tabulator)
//		autofill_last_word_from_ls(); // or program?

}

static void		shell_keypress(char *rc, char *ls, char *rrs, t_prog *prog)
{
	if (!rc[0])
		return ;
	if (is_special_key(rc))
		do_special_keys(rc, ls, rrs, prog);
	else if (ft_strlen(ls) < 2047)
		ft_strncat(ls, rc, 1);
// some kind of print clear row, print prompt again, 
}

int				read_input(t_input *input)
{
	char	read_chars[10];
	char	*left_side; // this is not enough, maybe make it dynamic?
	char	*reverse_right_side;

	if (!(left_side = ft_memalloc(sizeof(2048))))
		exit(err_temp(ERR_MALLOC, ));
	if (!(reverse_right_side = ft_memalloc(sizeof(2048))))
	{
		free(left_side);
		exit(err_temp(ERR_MALLOC, job->orig_termios));
	}
	while (1)
	{
		ft_bzero(read_chars, 10);
		if (read(job->fd_stdin, read_chars, 10) == -1)
			err_temp(ERR_READ, NULL, prog->orig_termios);
		shell_keypress(read_chars, left_side, reverse_right_side, prog);
	}
}
*/

void			init_input2(t_input *input)
{
	ft_bzero(input, sizeof(t_input));
	if (!(input->ls = ft_memalloc(sizeof(char) * 2048)))
		exit(1);
//		ft_error(0, ENOMEM, "");
	if (!(input->rrs = ft_memalloc(sizeof(char) * 2048)))
	{
		free(input->ls);
		exit(1);
//		ft_error(0, ENOMEM, "");
	}
}
