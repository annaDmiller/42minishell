NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

EXEC_PRT = srcs/execution/pipe.c \
                srcs/execution/exec.c \
                srcs/execution/free.c \
                srcs/execution/tlib.c \
                srcs/execution/tlist.c \
		srcs/execution/utils.c \
                srcs/execution/minishell.c \
		srcs/execution/set_execve.c \
                srcs/execution/processing.c \
		srcs/execution/expand_before_parsing.c \

PARSING_PRT = srcs/parsing/adding_arguement.c \
		srcs/parsing/handle_dollar.c \
		srcs/parsing/parse_env_value.c \
		srcs/parsing/handle_input_redir.c \
		srcs/parsing/input_from_stdin.c \
		srcs/parsing/handle_output_redir.c \
		srcs/parsing/handle_quotes.c \
		srcs/parsing/handle_redirection.c \
		srcs/parsing/handle_word.c \
		srcs/parsing/main_parsing.c \
		srcs/parsing/parsing_cmd.c \
		srcs/parsing/parsing_utils.c \
		srcs/finalization/error_logic.c \
		srcs/finalization/free_logic.c \
		srcs/list_logic/arg.c \
		srcs/list_logic/cmd.c \
		srcs/signal/init_signal.c \
		srcs/signal/signal_handlers.c \
		srcs/signal/sigint_hdl_while_child.c  \
		srcs/lexer/validate_input.c
		# srcs/finalization/exit_logic.c \

TEST = srcs/main.c \
	# unit.c \

BUILTINS = srcs/builtins/builtins.c \
		srcs/builtins/env.c \
		srcs/builtins/cd.c \
		srcs/builtins/pwd.c \
		srcs/builtins/echo.c \
		srcs/builtins/exit.c \
		srcs/builtins/unset.c \
		srcs/builtins/export.c \

SRCS = $(PARSING_PRT) $(TEST) $(EXEC_PRT) $(BUILTINS)

OBJS = $(SRCS:.c=.o)

.c.o:
	@$(CC) $(CFLAGS) -c -o $@ $< 

all: $(NAME)
        
$(NAME): $(OBJS)
	@make -C libft
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) -L./libft -lft -lreadline
	@echo "\033[1m	           _       _     _          _ _\n\
		 _ __ ___ (_)_ __ (_)___| |__   ___| | |\n\
		| '_ \` _ \| | '_ \| / __| '_ \ / _ \ | |\n\
		| | | | | | | | | | \__ \ | | |  __/ | |\n\
		|_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|\n\n\033[0m"

clean:
	@make clean -C libft
	@rm -rf $(OBJS)
	@echo "c'est clean"

fclean: clean
	@make fclean -C libft
	@rm -rf $(NAME)
	@echo "c'est fclean"

re: fclean all

.PHONY: all, clean, fclean, re
