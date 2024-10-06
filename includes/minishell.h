#ifndef MINISHELL_H
#define MINISHELL_H
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include "structures.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>

char    *print_prompt(void);
#endif