# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helvi <helvi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2021/03/18 21:29:42 by helvi            ###   ########.fr        #
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
DIR_OBJS = objs/
DIR_DEBUG = srcs/debug/

_SRC_MAIN = main.c

_SRC_INPUT = read_input_user.c \
			disable_raw_mode.c \
			enable_raw_mode.c \
			errors.c \
			ft_putc.c \
			init_input.c \
			prompt.c

_SRC_PARSER = 	parser.c \
				lexer.c \
				tokens.c \
				state_machine.c \
				stat_functions.c

_SRC_SIGNAL = signal.c

_SRC_DEBUG = 	arrows.c \
				input.c \
				minishell.c \
				rawmode.c \
				screen_printing.c \
				text_editing.c \
				command_list.c


SRC_MAIN = $(addprefix $(DIR_MAIN), $(_SRC_MAIN))
SRC_INPUT = $(addprefix $(DIR_INPUT), $(_SRC_INPUT))
SRC_PARSER = $(addprefix $(DIR_PARSER), $(_SRC_PARSER))
SRC_SIGNAL = $(addprefix $(DIR_SIGNAL), $(_SRC_SIGNAL))
SRC_DEBUG = $(addprefix $(DIR_DEBUG), $(_SRC_DEBUG))

SRC = $(SRC_MAIN) $(SRC_INPUT) $(SRC_PARSER) $(SRC_SIGNAL)
DEBUG_SRC = $(SRC_DEBUG) $(SRC_PARSER) $(SRC_SIGNAL)

_SRC = $(_SRC_MAIN) $(_SRC_INPUT) $(_SRC_PARSER) $(_SRC_SIGNAL)
_DEBUG_SRC = $(_SRC_DEBUG) $(_SRC_PARSER) $(_SRC_SIGNAL)

OBJ_FILES = $(_SRC:.c=.o)
DEBUG_OBJ_FILES = $(_DEBUG_SRC:.c=.o)

OBJS = $(patsubst %, $(DIR_OBJS)%, $(_SRC:.c=.o))
DEBUG_OBJS = $(patsubst %, $(DIR_OBJS)%, $(_DEBUG_SRC:.c=.o))

_INC = 	input.h \
		structs_21.h \
		includes.h \
		parser.h \
		ft_debug.h \
		ft_signal.h

INC = $(addprefix $(DIR_INC), $(_INC))

all: libft $(NAME)

$(NAME): $(DIR_OBJS) $(OBJS) libft
		$(CC) $(CFLAGS) $(TERMCAPS) -o $(NAME) $(OBJS) libft.a

debug : $(DIR_OBJS) $(DEBUG_OBJS) libft
		$(CC) $(CFLAGS) -o $(NAME) $(DEBUG_OBJS) libft.a

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

$(DIR_OBJS)%.o: $(DIR_DEBUG)%.c $(INC)
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
