NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -pthread -O3 -g3 

SRC = srcs/tmpmain.c \
	
PIPEX = pipex/pipex.c \
	pipex/split.c \
	pipex/utils.c \
	pipex/execute.c \
	pipex/process.c \

OBJS = $(SRC:.c=.o)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $< 

all: $(NAME)
        
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	echo "\033[1m____________________________________________\n____________________________________________\n_____________                  _____________\n____________    MINISHELL       ____________\n_____________        READY     _____________\n____________________________________________\n____________________________________________\n\033[0m"

clean:
	rm -rf $(OBJS)
	echo "c'est clean"

fclean: clean
	rm -rf $(NAME)
	echo "c'est fclean"

re: fclean all

.PHONY: all, clean, fclean, re

.SILENT:
