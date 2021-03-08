# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helvi <helvi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/25 12:15:31 by helvi             #+#    #+#              #
#    Updated: 2021/02/25 14:06:21 by helvi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libftstrigarrays.a

_SRC = 	ft_addstr.c \
		ft_array_length.c \
		ft_strarr_add.c \
		ft_strarr_addfront.c \
		ft_strarr_copy.c \
		ft_strarray_free.c

_OBJ = $(_SRC:.c=.o)
_INC = stringarrays.h

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
	@echo "\n"libft stringarray objects done."\n"

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
