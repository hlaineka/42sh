# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2021/04/28 17:51:52 by hlaineka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR)

FT_ERROR_DIR = ft_error/
FT_EXIT_DIR = ft_exit/
FT_PRINTF_DIR = ft_printf/
INC_DIR = includes/
LIBFT_DIR = libft/
LISTS_DIR = lists/
MISC_DIR = misc/
OBJS_DIR = objs/
STRINGARRAYS_DIR = stringarrays/
STRINGS_DIR = strings/

_SRC_FT_ERROR = ft_error.c \
				float_trim_and_round.c \
				ft_print.c \
				helper_functions.c \
				print_c.c \
				print_d.c \
				print_f.c \
				print_o.c \
				print_p.c \
				print_s.c \
				print_u.c \
				print_x.c \
				set_command_values.c \
				va_arg_reader_functions.c

_SRC_FT_EXIT = ft_exit.c

_SRC_FT_PRINTF = convert_di.c \
			ft_arg_convert.c \
			ft_asterisk.c \
			ft_char.c \
			ft_do_flags.c \
			ft_dprintf.c \
			ft_field_width.c \
			ft_flags_fun.c \
			ft_ftoa_bit.c \
			ft_initialize.c \
			ft_padding.c \
			ft_parse.c \
			ft_percent.c \
			ft_precision.c \
			ft_printf.c \
			ft_printf_fd.c \
			ft_ptr.c \
			ft_reset.c \
			ft_str.c \
			ft_str_to_lst.c \
			ft_tools.c \
			get_format_id.c \
			get_variable.c \
			get_variable_info.c

_SRC_LIBFT = ft_abs.c \
			ft_array_len.c \
			ft_atoi.c \
			ft_atoi_base.c \
			ft_bitmask.c \
			ft_bzero.c \
			ft_frexp.c \
			ft_ftoa.c \
			ft_intlen_base.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_iscntrl.c \
			ft_isdigit.c \
			ft_isoption.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_itoa.c \
			ft_itoa_base_prefix.c \
			ft_log10.c \
			ft_longlonglen_base.c \
			ft_lstadd.c \
			ft_lstaddafter.c \
			ft_lstappend.c \
			ft_lstdel.c \
			ft_lstdelone.c \
			ft_lstfree.c \
			ft_lstiter.c \
			ft_lstlen.c \
			ft_lstmap.c \
			ft_lstnew.c \
			ft_lstnewtoend.c \
			ft_lstprint.c \
			ft_lstrev.c \
			ft_lstsrc.c \
			ft_ltoa_base.c \
			ft_ltoa_base_prefix.c \
			ft_memalloc.c \
			ft_memccpy.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_pow.c \
			ft_putchar.c \
			ft_putendl.c \
			ft_putnbr.c \
			ft_putstr.c \
			ft_strarrdel.c \
			ft_strarrlen.c \
			ft_strcat.c \
			ft_strchr.c \
			ft_strclr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlen.c \
			ft_strmap.c \
			ft_strmapi.c \
			ft_strncat.c \
			ft_strnchr.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strrcat.c \
			ft_strrchr.c \
			ft_strset.c \
			ft_strsplit.c \
			ft_strstr.c \
			ft_strsub.c \
			ft_strtrim.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_uintlen_base.c \
			ft_uintmaxlen_base.c \
			ft_uintmaxtoa_base.c \
			ft_uitoa_base.c \
			ft_ull_len_base.c \
			ft_vlqnew.c \
			get_nbr.c

_SRC_LISTS = ft_lst_length.c \
			ft_lst_merge_sort.c \
			ft_lst_reverse.c \
			ft_lst_sorted_merge.c \
			ft_lst_split.c \
			ft_lstaddtoend.c \
			ft_lstdellast.c \
			ft_lstend.c

_SRC_MISC =	ft_free.c \
			ft_is_whitespace.c \
			ft_itoa_base.c \
			ft_itoa_float.c \
			ft_itoa_hexa.c \
			ft_itoa_uint.c \
			get_next_line.c \
			print_error.c \
			print_error_and_exit.c

_SRC_STRINGARRAYS = ft_addstr.c \
			ft_array_length.c \
			ft_strarr_add.c \
			ft_strarr_addfront.c \
			ft_strarr_copy.c \
			ft_strarray_free.c

_SRC_STRINGS = ft_char_str_join.c \
			ft_dynamic_string.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_remove_chars.c \
			ft_replace_char.c \
			ft_str_addi.c \
			ft_str_char_join.c \
			ft_str_deli.c \
			ft_str_find_c.c \
			ft_str_realloc.c \
			ft_str_rfind_c.c \
			ft_str_toupper.c \
			ft_strjoin3.c \
			ft_strjoin_frees1.c \
			ft_strjoin_frees2.c \
			ft_strlast.c \
			ft_strpaste.c \
			ft_strpaste_digits.c \
			ft_strpaste_end.c \
			ft_strstr_remove.c \
			ft_strstri.c \
			ft_strsub_freestr.c \
			ft_strsub_mid.c \
			ft_strtoupper.c \
			ft_strcut.c \
			ft_is_nbrstr.c

SRC_FT_ERROR = $(addprefix $(FT_ERROR_DIR), $(_SRC_FT_ERROR))
SRC_FT_EXIT = $(addprefix $(FT_EXIT_DIR), $(_SRC_FT_EXIT))
SRC_FT_PRINTF = $(addprefix $(FT_PRINTF_DIR), $(_SRC_FT_PRINTF))
SRC_LIBFT = $(addprefix $(LIBFT_DIR), $(_SRC_LIBFT))
SRC_LISTS = $(addprefix $(LISTS_DIR), $(_SRC_LISTS))
SRC_MISC = $(addprefix $(MISC_DIR), $(_SRC_MISC))
SRC_STRINGARRAYS = $(addprefix $(STRINGARRAYS_DIR), $(_SRC_STRINGARRAYS))
SRC_STRINGS = $(addprefix $(STRINGS_DIR), $(_SRC_STRINGS))

SRC = $(SRC_FT_ERROR) $(SRC_FT_EXIT) $(SRC_FT_PRINTF) $(SRC_LIBFT) \
		$(SRC_LISTS) $(SRC_MISC) $(SRC_STRINGARRAYS) $(SRC_STRINGS)

_SRC = $(_SRC_FT_ERROR) $(_SRC_FT_EXIT) $(_SRC_FT_PRINTF) $(_SRC_LIBFT) \
		$(_SRC_LISTS) $(_SRC_MISC) $(_SRC_STRINGARRAYS) $(_SRC_STRINGS)

OBJ_FILES = $(_SRC:.c=.o)
OBJS = $(patsubst %, $(OBJS_DIR)%, $(_SRC:.c=.o))

_INC = 	ft_error.h \
		ft_exit.h \
		ft_printf.h \
		ft_printf_typedefs.h \
		libft.h \
		libft_shorthand.h \
		lists.h \
		misc.h \
		stringarrays.h \
		strings.h
INC = $(addprefix $(INC_DIR), $(_INC))

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
		ar rc $(NAME) $(OBJS) $(INC)
		ranlib $(NAME)

$(OBJS_DIR):
		mkdir -p $(OBJS_DIR)

$(OBJS_DIR)%.o: $(FT_ERROR_DIR)%.c
		$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)%.o: $(FT_EXIT_DIR)%.c
		$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)%.o: $(FT_PRINTF_DIR)%.c
		$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)%.o: $(LIBFT_DIR)%.c
		$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)%.o: $(LISTS_DIR)%.c
		$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)%.o: $(MISC_DIR)%.c
		$(CC) $(CFLAGS) -o $@ -c $<

$(OBJS_DIR)%.o: $(STRINGARRAYS_DIR)%.c
		$(CC) $(CFLAGS) -o $@ -c $<
		
$(OBJS_DIR)%.o: $(STRINGS_DIR)%.c
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@rm -f $(OBJS)
	@echo library object files removed.

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJS_DIR)
	@echo library .a file removed. Object folder removed.

re: fclean all
