/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_typedefs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhuhtane <hhuhtane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 12:33:21 by hhuhtane          #+#    #+#             */
/*   Updated: 2020/10/16 16:24:48 by hhuhtane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TYPEDEFS_H
# define FT_PRINTF_TYPEDEFS_H

# include "libft.h"

/*
***********************
**   DEFINE MACROS   **
***********************
** FLAGS - macros **
********************
** - if you add more flags, remember to change FLAGS_SIZE **
*/
# define FLAGS "#0- +"
# define FLAGS_SIZE 5
# define FLAGS_MASK 31
# define HASH_INDEX 0
# define ZERO_INDEX 1
# define MINUS_INDEX 2
# define SPACE_INDEX 3
# define PLUS_INDEX 4
# define STAR_INDEX 5
# define DOLLAR_INDEX 6
# define APOSTROPHE_INDEX 7
# define CDINPSU_MASK 245768

/*
** PRECISION - macros
*/
# define PRECISION_INDEX 8

/*
** LENGTH MODIFIERS - macros
*/
# define L_MODIFIER "hhllL"
# define L_MOD_MASK 15872
# define L_MOD_INDEX 9
# define L_MOD_LAST 13
# define L_MOD_SIZE 5
# define H_INDEX 9
# define HH_INDEX 10
# define L_INDEX 11
# define LL_INDEX 12
# define UPL_INDEX 13

/*
** CONVERSION SPECIFIERS
*/
# define FORMAT_MASK 4095
# define FORMAT_ID "diouxXeEfFgGaACcSspnb%"
# define FORMAT_ID_SIZE 22
# define DIOUXX_MASK 63
# define OUXX_MASK 60
# define AAEEFFGG_MASK 16320
# define DI_MASK 3
# define D_INDEX 0
# define I_INDEX 1
# define O_INDEX 2
# define U_INDEX 3
# define X_INDEX 4
# define UPX_INDEX 5
# define E_INDEX 6
# define UPE_INDEX 7
# define F_INDEX 8
# define UPF_INDEX 9
# define G_INDEX 10
# define UPG_INDEX 11
# define A_INDEX 12
# define UPA_INDEX 13
# define UPC_INDEX 14
# define C_INDEX 15
# define UPS_INDEX 16
# define S_INDEX 17
# define P_INDEX 18
# define N_INDEX 19
# define B_INDEX 20
# define PERCENT_INDEX 21

# define PREFIX 2

/*
**************
** TYPEDEFS **
**************
*/

typedef struct			s_bitshift
{
	unsigned long long	m : 63;
	unsigned long long	integer : 1;
	unsigned short		exp : 15;
	unsigned short		sign : 1;
}						t_bitshift;

typedef union			u_ldbits
{
	long double			ld;
	t_bitshift			bits;
}						t_ldbits;

typedef union			u_backtold
{
	unsigned long long	m;
	long double			ld;
}						t_backtold;

typedef struct			s_all
{
	char				*format_ptr;
	va_list				args;
	t_list				*parsed_args;
	t_list				*last_arg;
	size_t				*len;

	char				flags_str[FLAGS_SIZE + 1];
	char				l_modifier_str[L_MOD_SIZE + 1];
	char				format_id_str[FORMAT_ID_SIZE + 1];
	void				(*convert_fun_ptr[FORMAT_ID_SIZE])(void*);
	void				(*flags_fun_ptr[FLAGS_SIZE])(void*);

	int					format_info;
	size_t				width;
	size_t				precision;
	int					format_id;

	intmax_t			arg_int;
	uintmax_t			arg_uint;
	long double			arg_double;
	char				*arg_str;
	void				*arg_ptr;
	size_t				arg_len;
	int					arg_base;
	size_t				combined_len;

	char				prefix[PREFIX + 1];
	size_t				prefix_len;
	char				padding_char;
	size_t				padding_len;
	char				*padding_str;
	char				*convert_str;
	char				*full_str;
}						t_all;

#endif
