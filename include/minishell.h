/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:54:17 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 08:48:04 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIHELL_H
# define MINIHELL_H

# include "pipex.h"
# include "ministruct.h"
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


void	minishell(struct msh *msh, int argc, char **argv, char **env);

///// processing.c
void    everyinit(struct msh *msh, int argc, char **argv, char **envp);
///// processing.c

///// BUILTINS.c
void    env(t_msh *msh);
void    pwd(t_msh *msh);
void	echo(t_msh *msh, char *str);
///// BUILTINS.c
void    cd(t_msh *msh, char *path);
void    up_pwd(struct msh *msh, char *dir);
void    down_pwd(struct msh *msh);

///// EXPAND.c
char	*expand(struct msh *msh, char *str);
///// EXPAND.c


///// REDIR.c
void	redirin(char *str, char *file); // will take care of "<"
void	redirout(char *str, char *file); // will take care of ">"
void	append(char *str, char *file); // will take care of ">>"
void	heredoc(char *str); // will take care of "<<"
char	*fpath_tt(char *cmd, int i); // find the absolute path of a cmd so we can execve it
///// REDIR.c

///// ENV.c
void	envinit(struct msh *msh, char **env, int i); // init the linked list that will stock our env pointer
char	*env_var(char *str); // function to stock the content of the env variable
char	*env_varname(char *str); // function to stock the name of the variable
t_env	*env_retrieve_var(t_env *env, char *str); // funtion that retrieve the content of a variable base on it name
void	freenv(t_env *env); // free the linked list \\ "lst_env" leak l.23
///// ENV.c

///// UTILS.c
int	tstrlen(char *str);
char	*tstrdup(char *src);
char	*fpath(char **env, char *cmd, int i);
char	*tjoin(char *str, char *add);
char	*first_path(char *str);
///// UTILS.c

char	*gnl(int fd); // get_next_line

///// GNLV2.c
char	*save_static(char *str, int rv);
char	*org(char *str);
///// GNLV2.c

///// EXPORT.c
void	export_no_opt(struct msh *msh);
void	export_def(struct msh *msh, char *str);
int	tstrcmp(char *str, char *cmp);
///// EXPORT.c

///// UNSET.c
void    unset(struct msh *msh, char *str);
///// UNSET.c

#endif
