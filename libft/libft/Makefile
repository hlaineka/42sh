# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: helvi <helvi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2021/02/25 12:44:39 by helvi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

NAME = libft.a

_SRC = ft_itoa.c \
		ft_putchar.c \
		ft_putendl.c \
		ft_putnbr.c \
		ft_putstr.c \
		ft_strcpy.c \
		ft_strdup.c \
		ft_strlen.c \
		ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_strncpy.c \
		ft_strcat.c \
		ft_memchr.c \
		ft_strncat.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strstr.c \
		ft_strnstr.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_memalloc.c \
		ft_memdel.c \
		ft_strnew.c \
		ft_strdel.c \
		ft_strclr.c \
		ft_striter.c \
		ft_striteri.c \
		ft_strmap.c \
		ft_strmapi.c \
		ft_strequ.c \
		ft_strnequ.c \
		ft_strsub.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_strsplit.c \
		ft_lstnew.c \
		ft_lstdelone.c \
		ft_lstdel.c \
		ft_lstadd.c \
		ft_lstiter.c \
		ft_lstmap.c \
		ft_lstaddafter.c \
		ft_lstnewtoend.c \
		ft_strset.c \
		ft_lstsrc.c \
		ft_strnchr.c \
		ft_iscntrl.c \
		ft_define_length.c
 
_OBJ = $(_SRC:.c=.o)
_INC = libft.h

SRC_DIR = .
OBJ_DIR = ../objs
INC_DIR = ../includes

SRC = $(patsubst %,$(SRC_DIR)/%,$(_SRC))
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))
INC = $(patsubst %,$(INC_DIR)/%,$(_INC))

FLAGS = -Wall -Wextra -Werror -I $(INC_DIR)
DEBUG_FLAGS = -Wall -Wextra -Werror -g -I $(INC_DIR)

all: $(OBJ_DIR) $(NAME)

$(NAME): $(OBJ)
	@echo "\n"libft objects done."\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC)
	@printf "|"
	@$(CC) $(DEBUG_FLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

mclean: fclean

re: fclean all
