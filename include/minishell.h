/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:54:17 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/18 20:24:41 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H

# include "pipex.h"
# include "structures.h"
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


void	minishell(t_msh *msh, int argc, char **argv, char **env);

///// processing.c
void    everyinit(t_msh *msh, int argc, char **argv, char **envp);
void	putstr(char *str);
///// processing.c

///// BUILTINS.c
void    env(t_env *env);
void    pwd(t_msh *msh);
void	echo(t_msh *msh, t_args *argv);
char	*expand(t_msh *msh, char *str);
///// BUILTINS.c

///// CD.c
void    cd(t_msh *msh, t_args *argv);
void    up_pwd(t_msh *msh, char *dir);
void    down_pwd(t_msh *msh);
///// CD.c

///// REDIR.c
void	redirin(char *str, char *file); // will take care of "<"
void	redirout(char *str, char *file); // will take care of ">"
void	append(char *str, char *file); // will take care of ">>"
void	heredoc(char *str); // will take care of "<<"
///// REDIR.c

///// ENV.c
void	envinit(t_msh *msh, char **env, int i); // init the linked list that will stock our env pointer
void	env_build(t_msh *msh, int i); // build env if there is no env available
char	*env_var(char *str); // function to stock the content of the env variable
char	*env_varname(char *str); // function to stock the name of the variable
t_env	*env_retrieve_var(t_env *env, char *str); // funtion that retrieve the content of a variable base on it name
///// ENV.c

///// GNL
char	*gnl(int fd); // get_next_line
char	*save_static(char *str, int rv);
char	*org(char *str);
///// GNL

///// EXPORT.c
void	export(t_msh *msh, t_args *argv);
void	export_no_opt(t_msh *msh);
void	export_def(t_msh *msh, t_args *argv);
///// EXPORT.c

///// UNSET.c
char	*setup_name(char *str);
void    unset(t_msh *msh, t_args *argv);
///// UNSET.c

///// FREE.c
void	freecmdline(t_args *arg);
void	freenv(t_env *env); // free env linked list 
void	wegotasplituation(struct spt x); // free split if there is an error in it
///// FREE.c

///// TLIB.c
void	show_args(t_msh *msh);
int	tstrcmp(char *str, char *cmp);
int	tstrlen(char *str);
char	*tstrdup(char *src);
char	*tjoin(char *str, char *add);
void	putstrfd(char *str, int fd);
void	fsplit(char **str);
///// TLIB.c

///// TLIST.c
int	l_envsize(t_env *env);
int	l_argsize(t_args *argv);
///// TLIST.c

void	texit(t_msh *msh, t_args *argv);

void	parse_cmd_line(t_msh *msh, char **argv);

///// EXEC.c
// int	exec(t_msh *msh, t_cmd *cmd);
int	exec(t_msh *msh, t_args *arg);
// char	**setup_args(t_args *argv);
char	**setup_args(char *name, t_args *argv);
char	**setup_env(t_env *env);
char	*fpath_tt(char *cmd, int i); // find the absolute path of a cmd so we can execve it
///// EXEC.c

#endif
