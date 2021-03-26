/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_user.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 17:34:41 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/03/17 19:28:13 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "input.h"


void			ft_putchar_input(char c, int x, int y, int col_limit)
{
	x--;
	y--;
	x += write(STDOUT_FILENO, &c, 1);
	if (x == col_limit)
	{
		write(STDOUT_FILENO, "\n\r", 2);
		x = 0;
		y++;
	}
}

void			ft_putstr_input(char *str, int x, int y, int col_limit)
{
	int		i;

	x--;
	y--;
	i = 0;
	while (str[i])
	{
		x += write(STDOUT_FILENO, &str[i++], 1);
		if (x == col_limit)
		{
			write(STDOUT_FILENO, "\n\r", 2);
			x = 0;
			y++;
		}
	}
//	ft_printf("moi");
}


void			ft_putrstr_input(char *str, int x, int y, int col_limit)
{
//	int		x;
//	int		y;
	int		len;

//	x = *col - 1;
//	y = *row - 1;
	x--;
	y--;
	len = ft_strlen(str);
	while (len-- > 0)
	{
		x += write(STDOUT_FILENO, &str[len], 1);
		if (x == col_limit)
		{
			write(STDOUT_FILENO, "\n\r", 2);
			x = 0;
			y += 1;
		}
	}
}

int				move_cursor_up(int *row, int *col, t_term *term)
{
	if (*row == 1)
		return (0);
	*row = *row - 1;
	tputs(tgoto(term->cm_string, *col - 1, *row - 1), 1, ft_putc);
	return (1);
}

int				move_cursor_down(int *row, int *col, t_term *term)
{
	*row = *row + 1;
	tputs(tgoto(term->cm_string, *col - 1, *row - 1), 1, ft_putc);
	return (1);
}

int				move_cursor_right(int *row, int *col, t_term *term)
{
	if (*col == (int)term->ncolumns)
	{
		*col = 1;
		*row = *row + 1;
	}
	else
		*col = *col + 1;
	tputs(tgoto(term->cm_string, *col - 1, *row - 1), 1, ft_putc);
	return (1);
}

int				move_cursor_left(int *row, int *col, t_term *term)
{
	if (*col == 1)
	{
		*col = term->ncolumns;
		*row = *row - 1;
	}
	else
		*col = *col - 1;
	tputs(tgoto(term->cm_string, *col - 1, *row - 1), 1, ft_putc);
	return (1);
}

static int		is_special_key(char *rc)
{
	if (rc != 0 && (rc[0] < 32 || rc[0] == 127)) // Is this correct?
		return (1);
	return (0);
}

void			move_nchars_from_s1_to_s2(char *s1, char *s2, int limit, int n)
{
	int		i1;
	int		i2;

	i1 = ft_strlen(s1) - 1;
	i2 = ft_strlen(s2);
	if (i1 < 0 || i2 >= limit)
		return ;
	while (n-- > 0)
	{
		s2[i2++] = s1[i1];
		s1[i1--] = '\0';
	}
	s2[i2] = '\0';
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

int		get_pos(int *y, int *x)
{
	char	buf[30];
	int		i;
	int		pow;
	char	ch;

	*y = 0;
	*x = 0;
	i = 0;
	ch = 0;
	ft_bzero(buf, sizeof(char) * 30);
	write(1, "\033[6n", 4);
	while (ch != 'R' || i > 30)
	{
		if (!(read(0, &ch, 1)))
		{
			ft_printf_fd(2, "cursor position reading failed.\n\r");
			return (-1);
		}
		buf[i] = ch;
//		printf("\n\rbuf[%d]: \t%c \t%d\n\r", i, ch, ch);
		i++;
	}
	if (i < 2)
	{
		ft_printf("i < 2\n\r");
		return(1);
	}
	pow = 1;
	i -= 2;
	while (buf[i] != ';' && i > 0)
	{
		*x = *x + (buf[i] - '0') * pow;
		pow *= 10;
		i--;
	}
	pow = 1;
	i--;
	while (buf[i] != '[' && i > 0)
	{
		*y = *y + ( buf[i--] - '0' ) * pow;
		pow *= 10;
	}
//	*y -= 1;
//	*x -= 1;
	return 0;
}

void			home_keypress(t_input *input, t_term *term)
{
	int		ls_len;

	ls_len = ft_strlen(input->ls);
	move_nchars_from_s1_to_s2(input->ls, input->rrs, input->rrs_size, ls_len);
	tputs(tgoto(term->cm_string, input->prompt_col - 1, input->prompt_row - 1), 1, ft_putc); // pois?
	get_pos(&input->cursor_row, &input->cursor_col); //USELESS?
}

void			end_keypress(t_input *input, t_term *term)
{
	int		ls_len;
	int		rrs_len;
	int		print_len;
	int		x;
	int		y;

	ls_len = ft_strlen(input->ls);
	rrs_len = ft_strlen(input->rrs);
	print_len = ls_len + rrs_len + input->prompt_length;
	y = (print_len / term->ncolumns) + (input->start_row - 1);
	x = (print_len % term->ncolumns) + (input->start_col - 1);
	move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, rrs_len);
	tputs(tgoto(term->cm_string, x, y), 1, ft_putc); // pois?
	get_pos(&input->cursor_row, &input->cursor_col); //USELESS?
}

void			move_prev_word(t_input *input, t_term *term)
{
	int		len;
	int		i;
	int		x;
	int		y;

	len = ft_strlen(input->ls);
	if (len < 1)
		return ;
	i = len - 1;
	while (i >= 0 && input->ls[i] && input->ls[i] == ' ')
		i--;
	while (i >= 0 && input->ls[i] && input->ls[i] != ' ')
		i--;
	i = len - i - 1;
//	y = (input->cursor_row - 1) - (i / term->ncolumns);
//	x = (input->cursor_col - 1) - (i % term->ncolumns);
	move_nchars_from_s1_to_s2(input->ls, input->rrs, input->ls_size, i);

	len = ft_strlen(input->ls) + input->prompt_length;
	y = input->start_row + (len / term->ncolumns) - 1;
	x = input->start_row + (len % term->ncolumns) - 1;

	tputs(tgoto(term->cm_string, x, y), 1, ft_putc); // pois?
	get_pos(&input->cursor_row, &input->cursor_col); //USELESS?
//	ft_printf("x:%d y:%d i:%d len:%d", x, y, i, len);
}

void			move_next_word(t_input *input, t_term *term)
{
	int		len;
	int		i;
	int		x;
	int		y;

	len = ft_strlen(input->rrs);
	if (len < 1)
		return ;
	i = len - 1;
	while (i > 0 && input->rrs[i] && input->rrs[i] != ' ')
		i--;
	while (i > 0 && input->rrs[i] && input->rrs[i] == ' ')
		i--;
	i = len - i - 1;
	move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, i);

	len = ft_strlen(input->ls) + input->prompt_length;
	y = input->start_row + (len / term->ncolumns) - 1;
	x = input->start_row + (len % term->ncolumns) - 1;

/*
	len = ft_strlen(input->ls);
	y = input->prompt_row + (len / term->ncolumns) - 1;
	x = input->prompt_row + (len % term->ncolumns) - 1;
*/

//	y = (i / term->ncolumns) + (input->cursor_row - 1);
//	x = (i % term->ncolumns) + (input->cursor_col - 1);
	tputs(tgoto(term->cm_string, x, y), 1, ft_putc); // pois?
	get_pos(&input->cursor_row, &input->cursor_col); //USELESS?
//	ft_printf("x:%d y:%d i:%d len:%d", x, y, i, len);
}

static int		do_special_keys(char *rc, t_input *input, t_term *term)
{
	(void)term; // probably not needed at all
	if (ft_is_home_key(rc))
		home_keypress(input, term);
	else if (ft_is_end_key(rc))
		end_keypress(input, term);
	else if (rc[0] == KEY_ESC)
	{
		if (ft_is_right_key(rc + 1))
			move_next_word(input, term);
		else if (ft_is_left_key(rc + 1))
			move_prev_word(input, term);
		else if (rc[1] == KEY_ESC)
		{
			if (rc[2] == 91)
			{
				if (rc[3] == 65)
				{
					if (ft_strlen(input->ls) > (term->ncolumns - input->start_col))
					{
						move_nchars_from_s1_to_s2(input->ls, input->rrs, input->rrs_size, term->ncolumns);
						move_cursor_up(&input->cursor_row, &input->cursor_col, term);
					}
				}
				else if (rc[3] == 66)
					if (ft_strlen(input->rrs) > (term->ncolumns - input->start_col))
					{
						move_nchars_from_s1_to_s2(input->rrs, input->ls, input->ls_size, term->ncolumns);
						move_cursor_down(&input->cursor_row, &input->cursor_col, term);
						
					}
				return 0;
			}
		}
		else if (rc[1] == 91)
		{

//			if (rc[2] == 65) // UP arrow
//				history_up(); //PSEUDO
//			if (rc[2] == 66) // DOWN arrow
//				history_down; //PSEUDO

			if (rc[2] == 67 && input->rrs[0]) // RIGHT arrow
			{
				move_cursor_right(&input->cursor_row, &input->cursor_col, term);
				move_char_from_s1_to_s2(input->rrs, input->ls, input->ls_size);
			}
//				move_char_from_rrs_to_ls;
			if (rc[2] == 68 && input->ls[0]) // LEFT arrow
			{
				move_cursor_left(&input->cursor_row, &input->cursor_col, term);
				move_char_from_s1_to_s2(input->ls, input->rrs, input->rrs_size);
//				move_char_from_ls_to_rrs;
			}
			if (rc[2] == 51 && rc[3] == 126) // NO LIMIT!!!
			{
				if (!input->rrs[0])
					return (0);
				input->rrs[ft_strlen(input->rrs) - 1] = '\0';
				ft_putrstr_input(input->rrs, input->cursor_col, input->cursor_row, term->ncolumns);
				tputs(term->dc_string, 1, ft_putc);
				tputs(tgoto(term->cm_string, input->cursor_col - 1, input->cursor_row - 1), 1, ft_putc);
			}
		}
	}
	else if (rc[0] == 127) // NO LIMIT!!!
	{
		if (!input->ls[0])
			return (0);
		move_cursor_left(&input->cursor_row, &input->cursor_col, term);
//		tputs(term->ce_string, 1, ft_putc);
		input->ls[ft_strlen(input->ls) - 1] = '\0';
		ft_putrstr_input(input->rrs, input->cursor_col, input->cursor_row, term->ncolumns);
		tputs(term->dc_string, 1, ft_putc);
		tputs(tgoto(term->cm_string, input->cursor_col - 1, input->cursor_row - 1), 1, ft_putc);
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
	else if (ft_strlen(input->ls) < input->ls_size) //increase size if not large enough
	{
		ft_strncat(input->ls, rc, 1024);
//		ft_putchar_fd(rc[0], STDOUT_FILENO);
		ft_putstr_input(rc, input->cursor_col, input->cursor_row, term->ncolumns);
		get_pos(&input->cursor_row, &input->cursor_col);
		ft_putrstr_input(input->rrs, input->cursor_col, input->cursor_row, term->ncolumns);
		tputs(tgoto(term->cm_string, input->cursor_col - 1, input->cursor_row - 1), 1, ft_putc);
	}

/*
	if (rc[0])
	{
		tputs(tgoto(term->cm_string, term->cursorcol - 1, term->cursorrow - 1), 1, ft_putc);
		tputs(term->cd_string, 1, ft_putc);
		ft_printf_fd(STDOUT_FILENO, "%s\n\r%s\n\r", input->ls, input->rrs);
//		save_cursor_position(term);
		ft_printf_fd(STDOUT_FILENO, "\n\rrow: %d, col: %d\n\r", term->cursorrow, term->cursorcol);
	}
*/

	return (ret);
// some kind of print clear row, print prompt again, 
}

t_clist			*command_to_history(t_input *input, char *str)
{
	t_clist	*new;

	if (!(new = ft_clstnew(str, ft_strlen(str) + 1)))
		return (NULL);
	new->prev = input->last_comm;
	new->next = input->history;
	input->history->prev = new;
	input->last_comm->next = new;
	return (new);
}

char			*read_input_tty(t_input *input, t_term *term)
{
	char	read_chars[1024];
	char	*ls; // this is not enough, maybe make it dynamic?
	char	*rrs;
	char	*str;

	ft_bzero(input->ls, input->ls_size);
	ft_bzero(input->rrs, input->rrs_size);
	ls = input->ls;
	rrs = input->rrs;
//	tputs(tgoto(term->cm_string, 0, 0), 1, ft_putc); // pois?

	get_pos(&input->start_row, &input->start_col); // USELESS?
	input->prompt_length = ft_printf_fd(STDOUT_FILENO, "$> "); //prompt to own
	get_pos(&input->prompt_row, &input->prompt_col);
	input->cursor_row = input->prompt_row;
	input->cursor_col = input->prompt_col;
	get_pos(&term->cursorrow, &term->cursorcol); //USELESS?
	while (1)
	{
		ft_bzero(read_chars, 1024);
//		if (read(term->fd_stdin, read_chars, 10) == -1)
		if (read(STDIN_FILENO, read_chars, 1024) == -1)
			err_fatal(ERR_READ, NULL, term);
		if (shell_keypress(read_chars, input, term))
		{
			if (!(str = ft_memalloc(sizeof(char) * (ft_strlen(ls) + ft_strlen(rrs)))))
				err_fatal(ERR_MALLOC, NULL, term);
			ft_strcat(str, input->ls);
			ft_strrcat(str, input->rrs);
			if (!(input->history = command_to_history(input, str)))
				err_fatal(ERR_MALLOC, NULL, term);
			break;
		}
	}
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
