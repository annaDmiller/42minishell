/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:54:17 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/06 17:13:44 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIHELL_H
# define MINIHELL_H

# include "pipex.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct msh
{
	int	argc;
	char	**env;
	char	**argv;
}		t_msh;

typedef enum w_type
{
	PIPE,
	cmd,
	file,
	redir,
}		t_type;

// void	minishell(struct msh *msh, int argc, char **argv, char **env);

void	redirin(char *str, char *file);
void	redirout(char *str, char *file);
void	append(char *str, char *file);
char	*fpath_tt(char *cmd, int i);


char	*gnl(int fd);
int	trouve(const char *str);
char	*tjoin(char *str, char *add);
char	*save_static(char *str, int rv);
char	*org(char *str);

#endif
