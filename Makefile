NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -g3 

MINISHELL = redir.c \
		free.c \
		tlib.c \
		tlist.c \
		builtins.c \
		minishell.c \
		processing.c \
		oldwork/split.c \
		temporary_parsing.c \

BUILTINS = builtins/env.c \
		builtins/cd.c \
		builtins/pwd.c \
		builtins/echo.c \
		builtins/exit.c \
		builtins/unset.c \
		builtins/export.c \

SRCS = $(MINISHELL) $(BUILTINS)

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

all: $(NAME)
        
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	echo "\033[1m	           _       _     _          _ _\n\
		 _ __ ___ (_)_ __ (_)___| |__   ___| | |\n\
		| '_ \` _ \| | '_ \| / __| '_ \ / _ \ | |\n\
		| | | | | | | | | | \__ \ | | |  __/ | |\n\
		|_| |_| |_|_|_| |_|_|___/_| |_|\___|_|_|\n\n\033[0m"

clean:
	rm -rf $(OBJS)
	echo "c'est clean"

fclean: clean
	rm -rf $(NAME)
	echo "c'est fclean"

re: fclean all

.PHONY: all, clean, fclean, re

.SILENT:
