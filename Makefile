# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hlaineka <hlaineka@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 12:00:35 by hlaineka          #+#    #+#              #
#    Updated: 2021/07/29 09:26:17 by hhuhtane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 42sh

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -I$(DIR_INC) -Ilibft/includes
TERMCAPS = -ltermcap

DIR_INC = includes/
DIR_MAIN = srcs/
DIR_INPUT = srcs/input/
DIR_HISTORY = srcs/input/history/
DIR_PARSER = srcs/parser/
DIR_JOB_CONTROL = srcs/job_control/
DIR_JOB_CREATION = srcs/execution/job_creation/
DIR_TOKENIZATION = srcs/parser/tokenization/
DIR_AST_CREATION = srcs/parser/ast_creation/
DIR_SIGNAL = srcs/signal/
DIR_BUILTIN = srcs/builtins/
DIR_CD = srcs/builtins/fun_cd/
DIR_ECHO = srcs/builtins/fun_echo/
DIR_FG = srcs/builtins/fun_fg/
DIR_BG = srcs/builtins/fun_bg/
DIR_JOBS = srcs/builtins/fun_jobs/
DIR_SETENV = srcs/builtins/fun_setenv/
DIR_UNSETENV = srcs/builtins/fun_unsetenv/
DIR_ENV = srcs/builtins/fun_env/
DIR_EXPORT = srcs/builtins/fun_export/
DIR_SET = srcs/builtins/fun_set/
DIR_UNSET = srcs/builtins/fun_unset/
DIR_EXECUTION = srcs/execution/
DIR_INIT = srcs/init/
DIR_FC = srcs/builtins/fun_fc/
DIR_TEST = srcs/builtins/fun_test/
DIR_TYPE = srcs/builtins/fun_type/
DIR_HASH = srcs/builtins/fun_hash/
DIR_ALIAS = srcs/builtins/fun_alias/
DIR_UNALIAS = srcs/builtins/fun_unalias/
DIR_OBJS = objs/

_SRC_MAIN = main.c

_SRC_INPUT = read_input_user.c \
			errors.c \
			ft_putc.c \
			prompt.c \
			ft_isarrows.c \
			ft_isshiftarrows.c \
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
			get_input_heredoc.c \
			cut_copy_paste.c \
			double_input_mem.c \
			react_to_eof.c \
			pre_prompt_jobs_check.c

_SRC_INIT = disable_raw_mode.c \
			enable_raw_mode.c \
			init_input.c

_SRC_PARSER = 	parser.c \

_SRC_TOKENIZATION = lexer.c \
					quote_removal.c \
					basic_tokens.c \
					basic_token_functions.c \
					basic_token_functions2.c \
					basic_token_functions3.c \
					operator_tokens.c \
					operator_tokens_functions.c \
					advanced_tokenization.c \
					word_assignment_marking.c \
					word_expansion.c \
					tilde_expansion.c \
					dollar_expansion.c \
					add_full_command.c \
					bang_history.c \
					alias_handling.c

_SRC_AST_CREATION = ast_creation.c \
					precedence.c \
					shunting_yard.c \
					ast_builder.c \
					ast_functions.c

_SRC_SIGNAL =	signal.c \
				signal_input.c \
				signal_execution.c \
				signal_execution2.c \
				signal_to_default.c \
				signal_to_ignore.c

_SRC_BUILTIN =	err_builtin.c \
				ft_getenv.c \
				ft_setenv.c \
				ft_unsetenv.c \
				get_arg_options.c \
				is_builtin.c \
				is_digit_str.c

_SRC_CD =	builtin_cd.c \
			find_path.c \
			ft_is_absolute_path.c \
			get_absolute_path.c \
			is_valid_path.c

_SRC_ECHO =	builtin_echo.c

_SRC_FG =	builtin_fg.c

_SRC_BG =	builtin_bg.c

_SRC_FC =	builtin_fc.c \
			fc_es.c

_SRC_TEST =	builtin_test.c \
			b_operand.c \
			c_operand.c \
			d_operand.c \
			e_operand.c \
			f_operand.c \
			g_operand.c \
			big_l_operand.c \
			p_operand.c \
			r_operand.c \
			big_s_operand.c \
			s_operand.c \
			u_operand.c \
			w_operand.c \
			x_operand.c \
			z_operand.c \
			bang_operand.c \
			identical_operand.c \
			notidentical_operand.c \
			eq_operand.c \
			ne_operand.c \
			gt_operand.c \
			ge_operand.c \
			lt_operand.c \
			le_operand.c

_SRC_JOBS =	builtin_jobs.c \
			print_active_job.c

_SRC_SETENV =	builtin_setenv.c

_SRC_UNSETENV =	builtin_unsetenv.c

_SRC_ENV = 	builtin_env.c \
			env_functions.c

_SRC_EXPORT = builtin_export.c \
				get_name_and_value.c

_SRC_SET = builtin_set.c

_SRC_UNSET = builtin_unset.c

_SRC_JOB_CONTROL =	do_job_notification.c \
					find_last_stopped_job.c \
					find_pgid_job.c \
					get_current_job.c \
					get_job_status.c \
					is_job_completed.c \
					is_job_stopped.c \
					start_stopped_job.c \
					update_status.c

_SRC_EXECUTION =	execution.c \
					fork_and_chain_pipes.c \
					get_last_process.c \
					get_next_job_pgid.c \
					get_status_and_condition.c \
					simple_command.c \
					wait_to_get_status.c

_SRC_JOB_CREATION = job_creation.c \
					job_functions.c \
					job_functions2.c \
					token_null.c \
					tree_traversal.c \
					pipe_functions.c \
					redirection_functions.c \
					token_semi.c \
					token_pipe.c \
					token_great.c \
					token_less.c \
					token_dgreat.c \
					token_greatand.c \
					token_lessand.c \
					token_dless.c \
					token_or_if.c \
					token_and_if.c \
					token_and.c \
					token_assignment_word.c \
					check_fd.c \

_SRC_HISTORY =		add_cmd_to_history.c \
					bang_bang_fun.c \
					bang_minus_number_fun.c \
					bang_number_fun.c \
					bang_selector.c \
					bang_word_fun.c \
					get_last_history_index.c \
					incremental_history_search.c

_SRC_TYPE =			builtin_type.c

_SRC_HASH =			builtin_hash.c \
					is_in_hash_table.c \
					add_cmd_to_hash_table.c

_SRC_ALIAS=			builtin_alias.c \
					set_alias.c

_SRC_UNALIAS=		builtin_unalias.c

SRC_MAIN = $(addprefix $(DIR_MAIN), $(_SRC_MAIN))
SRC_INPUT = $(addprefix $(DIR_INPUT), $(_SRC_INPUT))
SRC_PARSER = $(addprefix $(DIR_PARSER), $(_SRC_PARSER))
SRC_JOB_CREATION = $(addprefix $(DIR_JOB_CREATION), $(_SRC_JOB_CREATION))
SRC_TOKENIZATION = $(addprefix $(DIR_TOKENIZATION), $(_SRC_TOKENIZATION))
SRC_AST_CREATION = $(addprefix $(DIR_AST_CREATION), $(_SRC_AST_CREATION))
SRC_SIGNAL = $(addprefix $(DIR_SIGNAL), $(_SRC_SIGNAL))
SRC_BUILTIN = $(addprefix $(DIR_BUILTIN), $(_SRC_BUILTIN))
SRC_CD = $(addprefix $(DIR_CD), $(_SRC_CD))
SRC_ENV = $(addprefix $(DIR_ENV), $(_SRC_ENV))
SRC_ECHO = $(addprefix $(DIR_ECHO), $(_SRC_ECHO))
SRC_FG = $(addprefix $(DIR_FG), $(_SRC_FG))
SRC_BG = $(addprefix $(DIR_BG), $(_SRC_BG))
SRC_EXPORT = $(addprefix $(DIR_EXPORT), $(_SRC_EXPORT))
SRC_SET = $(addprefix $(DIR_SET), $(_SRC_SET))
SRC_UNSET = $(addprefix $(DIR_UNSET), $(_SRC_UNSET))
SRC_JOBS = $(addprefix $(DIR_JOBS), $(_SRC_JOBS))
SRC_SETENV = $(addprefix $(DIR_SETENV), $(_SRC_SETENV))
SRC_UNSETENV = $(addprefix $(DIR_UNSETENV), $(_SRC_UNSETENV))
SRC_EXECUTION =  $(addprefix $(DIR_EXECUTION), $(_SRC_EXECUTION))
SRC_INIT =  $(addprefix $(DIR_INIT), $(_SRC_INIT))

SRC = $(SRC_MAIN) $(SRC_INPUT) $(SRC_PARSER) $(SRC_SIGNAL) $(SRC_BUILTIN) $(SRC_CD) $(SRC_ECHO) $(SRC_FG) $(SRC_SETENV) $(SRC_UNSETENV) $(SRC_ENV) $(SRC_EXECUTION) $(SRC_JOB_CREATION) $(SRC_TOKENIZATION) $(SRC_AST_CREATION) $(SRC_INIT) $(SRC_JOB_CONTROL) $(SRC_JOBS) $(SRC_BG) $(SRC_EXPORT) $(SRC_SET) $(SRC_UNSET)

_SRC = $(_SRC_MAIN) $(_SRC_INPUT) $(_SRC_PARSER) $(_SRC_SIGNAL) $(_SRC_BUILTIN) $(_SRC_CD) $(_SRC_ECHO) $(_SRC_FG) $(_SRC_SETENV) $(_SRC_UNSETENV) $(_SRC_ENV) $(_SRC_EXECUTION) $(_SRC_JOB_CREATION) $(_SRC_TOKENIZATION) $(_SRC_AST_CREATION) $(_SRC_INIT) $(_SRC_JOB_CONTROL) $(_SRC_JOBS) $(_SRC_BG) $(_SRC_HISTORY) $(_SRC_FC) $(_SRC_TEST) $(_SRC_TYPE) $(_SRC_HASH) $(_SRC_EXPORT) $(_SRC_SET) $(_SRC_UNSET) $(_SRC_ALIAS) $(_SRC_UNALIAS)

OBJ_FILES = $(_SRC:.c=.o)
OBJS = $(patsubst %, $(DIR_OBJS)%, $(_SRC:.c=.o))

_INC = 	input.h \
		structs_21.h \
		includes.h \
		parser.h \
		ft_signal.h \
		builtins.h \
		typedefs.h \
		execution.h \
		job_control.h \
		history.h

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

$(DIR_OBJS)%.o: $(DIR_FG)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_SETENV)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_ENV)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_UNSETENV)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_EXECUTION)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_INIT)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_JOB_CONTROL)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_JOBS)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_BG)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_HISTORY)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_FC)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_TEST)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_TYPE)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_HASH)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_EXPORT)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_SET)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_UNSET)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_ALIAS)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

$(DIR_OBJS)%.o: $(DIR_UNALIAS)%.c $(INC)
		$(CC) $(CFLAGS) -o $@ -c $<

libft:
	make -C libft
	cp libft/libft.a .

clean:
	@make -C libft clean
	@rm -f $(OBJS)
	@rm -f libft.a
	@echo library object files removed.

fclean: clean
	@make -C libft fclean
	@rm -f $(NAME)
	@rm -rf $(DIR_OBJS)
	@echo library .a file removed. Object folder removed.

re: fclean all
