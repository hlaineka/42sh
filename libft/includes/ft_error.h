/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 13:02:36 by helvi             #+#    #+#             */
/*   Updated: 2021/04/06 13:20:42 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ERROR_H
# define FT_ERROR_H

# include "libft.h"
# include "ft_exit.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdint.h>
# include <stdio.h>

/*
** A struct to save all the data about a command
*/
typedef struct s_tags
{
	char		specifier;
	int			positive_value;
	int			flag_zero;
	int			flag_minus;
	int			flag_plus;
	int			flag_space;
	int			flag_hash;
	int			flag_fd;
	int			width;
	int			width_address;
	int			precision;
	int			precision_address;
	int			length;
	int			length_hh;
	int			length_h;
	int			length_l;
	int			length_ll;
	int			length_lll;
	int			empty;
}				t_tags;

/*
** The main function to handle printing
*/

int				ft_printer(const char *format, va_list *source);

/*
** Helper functions to set command values
*/
void			set_flag(t_tags *command, char flag);
void			set_width(t_tags *command, char c, va_list *source);
void			set_precision(t_tags *command, char c, va_list *source);
void			set_length(t_tags *command, char c);
void			set_wildcard_precision(t_tags *command, va_list *source);

/*
** The fuctions called by selector on ft_printf, main functions
** to handle different data types.
*/
int				print_s(t_tags *command, va_list *source);
int				print_c(t_tags *command, va_list *source);
int				print_p(t_tags *command, va_list *source);
int				print_d(t_tags *command, va_list *source);
int				print_o(t_tags *command, va_list *source);
int				print_u(t_tags *command, va_list *source);
int				print_x(t_tags *command, va_list *source);
int				print_f(t_tags *command, va_list *source);

/*
** Helper functions
*/
uintmax_t		read_octal(t_tags *command, va_list *source);
long long int	read_int(t_tags *command, va_list *source);
long double		read_float(t_tags *command, va_list *source);
uintmax_t		read_hexa(t_tags *command, va_list *source);
void			int_width_flag_zero(char *returnable, char *string,
					t_tags *command);
void			float_width_flag_zero(char *returnable, char *string,
					t_tags *command);
void			uint_width_flag_zero(char *returnable, char *string,
					t_tags *command);
char			*ft_trim(char *str, t_tags *command);
long double		ft_round(long double number, t_tags *command);
char			*hexa_upperalpha(char *string);
int				is_specifier(char c);

#endif
