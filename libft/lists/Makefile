# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helvi <helvi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/24 15:52:44 by helvi             #+#    #+#              #
#    Updated: 2021/02/25 14:06:08 by helvi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libftlists.a

_SRC = 	ft_lst_length.c \
		ft_lst_merge_sort.c \
		ft_lst_reverse.c \
		ft_lst_sorted_merge.c \
		ft_lst_split.c \
		ft_lstaddtoend.c \
		ft_lstdellast.c \
		ft_lstend.c

_OBJ = $(_SRC:.c=.o)
_INC = lists.h

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
	@echo "\n"libft lists objects done."\n"

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
