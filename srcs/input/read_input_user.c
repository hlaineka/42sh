/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:34:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/12 20:36:05 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"

static int		is_special_key(char *rc)
{
	if (rc != 0 && (rc[0] < 32 || rc[0] == 127)) // Is this correct?
		return (1);
	return (0);
}

void			move_char_from_s1_to_s2(char *s1, char *s2, int s2_limit)
{
	int		i1;
	int		i2;

	i1 = ft_strlen(s1) - 1;
	i2 = ft_strlen(s2);
	if (i1 < 0 || i2 >= s2_limit)
		return ;
	s2[i2++] = s1[i1];
	s1[i1] = '\0';
	s2[i2] = '\0';
}

static int		do_special_keys(char *rc, t_input *input, t_term *term)
{
	(void)term; // probably not needed at all
	if (rc[0] == KEY_ESC)
	{
		if (rc[1] == 91)
		{

//			if (rc[2] == 65) // UP arrow
//				history_up(); //PSEUDO
//			if (rc[2] == 66) // DOWN arrow
//				history_down; //PSEUDO

			if (rc[2] == 67) // RIGHT arrow
				move_char_from_s1_to_s2(input->rrs, input->ls, input->ls_size);
//				move_char_from_rrs_to_ls;
			if (rc[2] == 68) // LEFT arrow
				move_char_from_s1_to_s2(input->ls, input->rrs, input->rrs_size);
//				move_char_from_ls_to_rrs;
		}
	}
//	else if (rc[0] == 13) // enter
//		dostuff();

//	if (rc == tabulator)
//		autofill_last_word_from_ls(); // or program?
	if (rc[0] == 13)
	{
		return (1);
	}
	return (0);
}


static int		shell_keypress(char *rc, t_input *input, t_term *term)
{
	int		ret;

	ret = 0;
	if (!rc[0])
		return (0);
	if (is_special_key(rc))
		ret = do_special_keys(rc, input, term);
//		return (1);
	else if (ft_strlen(input->ls) < input->ls_size) //increase size if not large enough
		ft_strncat(input->ls, rc, 1);
	tputs(tgoto(term->cm_string, 0, 0), 1, ft_putc);
	tputs(term->cd_string, 1, ft_putc);
//	ft_putstr(input->ls);
//	ft_putchar('|');
//	ft_putstr(input->rrs);

	ft_printf_fd(STDOUT_FILENO, "left:|%s| reverse right:|%s|", input->ls, input->rrs);
	return (ret);
// some kind of print clear row, print prompt again, 
}


/* THIS IS BONUS
char			*read_input_file(char *file, t_input *input)
{
	char	*line
}
*/

char			*read_input_tty(t_input *input, t_term *term)
{
	char	read_chars[10];
	char	*ls; // this is not enough, maybe make it dynamic?
	char	*rrs;
	char	*str;

	ls = input->ls;
	rrs = input->rrs;
	while (1)
	{
		ft_bzero(read_chars, 10);
//		if (read(term->fd_stdin, read_chars, 10) == -1)
		if (read(STDIN_FILENO, read_chars, 10) == -1)
			err_fatal(ERR_READ, NULL, term);
		if (shell_keypress(read_chars, input, term))
			break;
	}
	if (!(str = ft_memalloc(sizeof(char) * (ft_strlen(ls) + ft_strlen(rrs)))))
		err_fatal(ERR_MALLOC, NULL, term);
	ft_strcat(str, input->ls);
	ft_strrcat(str, input->rrs);
	return (str);
}

char			*get_input(int argc, char **argv, t_term *term, t_input *input)
{
	char	*str;

	str = NULL;
	if (argc == 1)
		str = read_input_tty(input, term);
	(void)argv;
//	else
//		read_input_file();
	return (str);
}
