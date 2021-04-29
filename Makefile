# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2021/04/29 14:24:09 by hlaineka         ###   ########.fr        #
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
DIR_JOB_CREATION = srcs/parser/job_creation/
DIR_TOKENIZATION = srcs/parser/tokenization/
DIR_AST_CREATION = srcs/parser/ast_creation/
DIR_SIGNAL = srcs/signal/
DIR_BUILTIN = srcs/builtins/
DIR_CD = srcs/builtins/fun_cd/
DIR_ECHO = srcs/builtins/fun_echo/
DIR_SETENV = srcs/builtins/fun_setenv/
DIR_UNSETENV = srcs/builtins/fun_unsetenv/
DIR_EXECUTION = srcs/execution/
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
			shell_keypress.c \
			copy_envp.c \
			clear_rows_starting_y.c \
			get_input_heredoc.c

_SRC_PARSER = 	parser.c \

_SRC_JOB_CREATION = job_creation.c \
					job_functions.c \
					token_null.c \
					tree_traversal.c \
					redirection_functions.c \
					token_semi.c \
					token_pipe.c \
					token_great.c \
					token_less.c \
					token_dgreat.c \
					token_greatand.c \
					token_dless.c

_SRC_TOKENIZATION = lexer.c \
					quote_removal.c \
					basic_tokens.c \
					basic_token_functions.c \
					basic_token_functions2.c \
					basic_token_functions3.c \
					operator_tokens.c \
					operator_tokens_functions.c \
					advanced_tokenization.c

_SRC_AST_CREATION = ast_creation.c \
					precedence.c \
					shunting_yard.c \
					ast_builder.c \
					ast_functions.c

_SRC_SIGNAL =	signal.c \
				signal_input.c \
				signal_execution.c \
				signal_to_default.c

_SRC_BUILTIN =	builtin_env.c \
				err_builtin.c \
				ft_getenv.c \
				ft_setenv.c \
				ft_unsetenv.c \
				is_builtin.c

_SRC_CD =	builtin_cd.c \
			find_path.c \
			ft_is_absolute_path.c \
			get_absolute_path.c \
			is_valid_path.c

_SRC_ECHO =	builtin_echo.c

_SRC_SETENV =	builtin_setenv.c

_SRC_UNSETENV =	builtin_unsetenv.c

_SRC_EXECUTION =	exec_tprocess.c \
					execution.c \
					simple_command.c \
					fork_and_chain_pipes.c


SRC_MAIN = $(addprefix $(DIR_MAIN), $(_SRC_MAIN))
SRC_INPUT = $(addprefix $(DIR_INPUT), $(_SRC_INPUT))
SRC_PARSER = $(addprefix $(DIR_PARSER), $(_SRC_PARSER))
SRC_JOB_CREATION = $(addprefix $(DIR_JOB_CREATION), $(_SRC_JOB_CREATION))
SRC_TOKENIZATION = $(addprefix $(DIR_TOKENIZATION), $(_SRC_TOKENIZATION))
SRC_AST_CREATION = $(addprefix $(DIR_AST_CREATION), $(_SRC_AST_CREATION))
SRC_SIGNAL = $(addprefix $(DIR_SIGNAL), $(_SRC_SIGNAL))
SRC_BUILTIN = $(addprefix $(DIR_BUILTIN), $(_SRC_BUILTIN))
SRC_CD = $(addprefix $(DIR_CD), $(_SRC_CD))
SRC_ECHO = $(addprefix $(DIR_ECHO), $(_SRC_ECHO))
SRC_SETENV = $(addprefix $(DIR_SETENV), $(_SRC_SETENV))
SRC_UNSETENV = $(addprefix $(DIR_UNSETENV), $(_SRC_UNSETENV))
SRC_EXECTUION =  $(addprefix $(DIR_EXECUTION), $(_SRC_EXECUTION))

SRC = $(SRC_MAIN) $(SRC_INPUT) $(SRC_PARSER) $(SRC_SIGNAL) $(SRC_BUILTIN) $(SRC_CD) $(SRC_ECHO) $(SRC_SETENV) $(SRC_UNSETENV) $(SRC_EXECUTION) $(SRC_JOB_CREATION) $(SRC_TOKENIZATION) $(SRC_AST_CREATION)

_SRC = $(_SRC_MAIN) $(_SRC_INPUT) $(_SRC_PARSER) $(_SRC_SIGNAL) $(_SRC_BUILTIN) $(_SRC_CD) $(_SRC_ECHO) $(_SRC_SETENV) $(_SRC_UNSETENV) $(_SRC_EXECUTION) $(_SRC_JOB_CREATION) $(_SRC_TOKENIZATION) $(_SRC_AST_CREATION)

OBJ_FILES = $(_SRC:.c=.o)
OBJS = $(patsubst %, $(DIR_OBJS)%, $(_SRC:.c=.o))

_INC = 	input.h \
		structs_21.h \
		includes.h \
		parser.h \
		ft_signal.h \
		builtins.h \
		typedefs.h \
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

$(DIR_OBJS)%.o: $(DIR_JOB_CREATION)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_TOKENIZATION)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_AST_CREATION)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_SIGNAL)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_BUILTIN)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_CD)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_ECHO)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_SETENV)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_UNSETENV)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_EXECUTION)%.c $(INC)
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
