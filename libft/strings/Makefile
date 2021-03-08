# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helvi <helvi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 11:52:58 by helvi             #+#    #+#              #
#    Updated: 2021/02/25 14:10:09 by helvi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libftstrigs.a

_SRC = 	ft_char_str_join.c \
		ft_dynamic_string.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_replace_char.c \
		ft_str_addi.c \
		ft_str_char_join.c \
		ft_str_deli.c \
		ft_str_find_c.c \
		ft_str_realloc.c \
		ft_str_rfind_c.c \
		ft_str_toupper.c \
		ft_strjoin_frees1.c \
		ft_strjoin_frees2.c \
		ft_strjoin3.c \
		ft_strlast.c \
		ft_strpaste_digits.c \
		ft_strpaste_end.c \
		ft_strpaste.c \
		ft_strstr_remove.c \
		ft_strstri.c \
		ft_strsub_freestr.c \
		ft_strsub_mid.c \

_OBJ = $(_SRC:.c=.o)
_INC = strings.h

SRC_DIR = .
OBJ_DIR = ../objs
INC_DIR = ../includes

SRC = $(patsubst %,$(SRC_DIR)/%,$(_SRC))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
INC = $(patsubst %,$(INC_DIR)/%,$(_INC))

INC_LIBFT = -I ../includes

FLAGS = -Wall -Wextra -Werror -I $(INC_DIR) $(INC_LIBFT)
DEBUG_FLAGS = -Wall -Wextra -Werror -g -I $(INC_DIR) $(INC_LIBFT)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "\n"libft strings objects done."\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	@printf "|"
	@$(CC) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all
