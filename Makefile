NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -O3 -g3 

SRC = oldwork/gnl.c \
	oldwork/gnlv2.c \
	oldwork/split.c \
	oldwork/utils.c \
	oldwork/pipex.c \
	oldwork/process.c \
	oldwork/execute.c \
	cd.c \
	env.c \
	redir.c \
	main.c \
	unset.c \
	export.c \
	expand.c \
	builtins.c \
	processing.c \

SRCS = $(SRC) $(PIPEX)

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
