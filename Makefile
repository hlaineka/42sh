# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2021/03/27 12:57:51 by hlaineka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I$(DIR_INC) -Ilibft/includes
TERMCAPS = -ltermcap

DIR_INC = includes/
DIR_MAIN = srcs/
DIR_INPUT = srcs/input/
DIR_PARSER = srcs/parser/
DIR_SIGNAL = srcs/signal/
DIR_EXECUTION = srcs/execution/
DIR_EXECUTION_CALLER = srcs/execution/execution_caller/
DIR_OBJS = objs/

_SRC_MAIN = main.c

_SRC_INPUT = read_input_user.c \
			disable_raw_mode.c \
			enable_raw_mode.c \
			errors.c \
			ft_putc.c \
			init_input.c \
			prompt.c \
			ft_isarrows.c \
			ft_iskey.c \
			ft_clstnew.c \
			ft_is_quote_open.c \
			ft_putstr_input.c \
			move_cursor.c \
			get_pos.c \
			move_chars.c \
			history_keypress.c \
			home_and_end_keypress.c \
			alt_direction_keypress.c \
			move_cursor_word.c \
			left_right_keypress.c \
			delete_keypress.c \
			ft_isdelete.c \
			shell_keypress.c

_SRC_PARSER = 	parser.c \
				lexer.c \
				tokens.c \
				token_functions.c \
				ast_creation.c

_SRC_SIGNAL = signal.c

_SRC_EXECUTION = execution.c

_SRC_EXECUTION_CALLER = execution_caller.c

SRC_MAIN = $(addprefix $(DIR_MAIN), $(_SRC_MAIN))
SRC_INPUT = $(addprefix $(DIR_INPUT), $(_SRC_INPUT))
SRC_PARSER = $(addprefix $(DIR_PARSER), $(_SRC_PARSER))
SRC_SIGNAL = $(addprefix $(DIR_SIGNAL), $(_SRC_SIGNAL))
SRC_EXECUTION_CALLER = $(addprefix $(DIR_EXECUTION_CALLER), $(_SRC_EXECUTION_CALLER))
SRC_EXECTUION =  $(addprefix $(DIR_EXECUTION), $(_SRC_EXECUTION))

SRC = $(SRC_MAIN) $(SRC_INPUT) $(SRC_PARSER) $(SRC_SIGNAL) $(SRC_EXECUTION) $(SRC_EXECUTION_CALLER)

_SRC = $(_SRC_MAIN) $(_SRC_INPUT) $(_SRC_PARSER) $(_SRC_SIGNAL) $(_SRC_EXECUTION) $(_SRC_EXECUTION_CALLER)

OBJ_FILES = $(_SRC:.c=.o)
OBJS = $(patsubst %, $(DIR_OBJS)%, $(_SRC:.c=.o))

_INC = 	input.h \
		structs_21.h \
		includes.h \
		parser.h \
		ft_signal.h \
		execution.h

INC = $(addprefix $(DIR_INC), $(_INC))

all: libft $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS) libft
		$(CC) $(CFLAGS) $(TERMCAPS) -o $(NAME) $(OBJS) libft.a

$(DIR_OBJS):
		make -C libft
		cp libft/libft.a .
		mkdir -p $(DIR_OBJS)

$(DIR_OBJS)%.o: $(DIR_MAIN)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_INPUT)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_PARSER)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_SIGNAL)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_EXECUTION)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_EXECUTION_CALLER)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

libft:
	make -C libft
	cp libft/libft.a .

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@rm -f libft.a
	@echo library object files removed.

fclean:
	@make -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(DIR_OBJS)
	@echo library .a file removed. Object folder removed.

re: fclean all