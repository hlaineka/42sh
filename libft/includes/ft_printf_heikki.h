/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 17:41:37 by hhuhtane          #+#    #+#             */
/*   Updated: 2021/02/12 15:36:57 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>

# include <stdarg.h>
# include "ft_printf_typedefs.h"
# include "libft_heikki.h"

/*
*************************
** FUNCTION PROTOTYPES **
*************************
*/
int				ft_printf(const char *format, ...);
int				ft_asprintf(char **ret, const char *format, ...);
int				ft_printf_fd(int fd, const char *format, ...);
int				ft_dprintf(int fd, const char *format, ...);
int				ft_initialize(t_all *all, const char *format, size_t *len);
int				ft_parse(t_all *all);
int				get_variable(t_all *all);
int				get_variable_info(t_all *all);
int				get_format_id(t_all *all);
int				ft_arg_convert(t_all *all);

void			convert_di(void *param);
void			convert_ouxx(void *param);
void			convert_double(void *param);
void			convert_percent(void *param);
void			convert_char(void *param);
void			convert_str(void *param);
void			convert_ptr(void *param);

int				ft_reset_format_info(t_all *all);

/*
***********
** FLAGS **
***********
*/
void			ft_do_flags(t_all *all);

void			ft_flag_hash(void *param);
void			ft_flag_zero(void *param);
void			ft_flag_minus(void *param);
void			ft_flag_space(void *param);
void			ft_flag_plus(void *param);

int				ft_field_width(t_all *all);
int				ft_variable_len(t_all *all);

void			combine_elements(t_all *all);
void			ft_full_str_to_list(t_all *all);
void			ft_precision(t_all *all);

void			get_percent(t_all *all);
void			get_char(t_all *all);
void			get_str(t_all *all);
void			get_ptr(t_all *all);

size_t			ft_precision_asterisk(t_all *all);
size_t			ft_width_asterisk(t_all *all);
int				ft_create_padding_str(t_all *all);

char			*ft_lftoa_bit(long double f, size_t prec, char *sign);
int				get_first_decimal(long double f);

void			future_feature(void *param);
#endif
