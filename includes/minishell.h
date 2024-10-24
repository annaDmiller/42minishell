/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:16:13 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/06 20:16:14 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
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
# include <signal.h>

# define PROMPT "minishell$ "
# define _GNU_SOURCE

extern volatile int g_sig;

//signals
void	init_signals(char prog, t_all *all);
void	sigint_hdl(int sig);
//list_logic
t_cmd   *cmd_new(t_all *all);
void    cmd_add_el_back(t_all *all, t_cmd *new_el);
t_cmd   *cmd_last_el(t_all *all);
t_args   *arg_new(t_all *all);
void    arg_add_el_back(t_cmd *last_cmd, t_args *new_el);
t_args   *arg_last_el(t_cmd *last_cmd);
//main part
char    *print_prompt(t_all *all);
int validate_line(t_all *all);
//parsing main
void    parse_line(t_all *all);
void    parse_cmd(t_all *all);
void    add_arg(t_all *all, t_cmd *last, char **str);
//parsing utils
int  is_white_space(char car);
int is_empty_line(char *cmd_line);
int is_quote(char car);
int is_redir(char car);
//parsing main functions
char	*handle_dollar(t_all *all, char car);
char    *handle_redir(t_all *all, t_cmd *cmd);
char *read_addr(t_all *all, t_cmd *cmd);
void    handle_input(t_all *all, t_cmd *cmd);
void    handle_output(t_all *all, t_cmd *cmd);
char	*handle_quotes(t_all *all, t_cmd *cmd, int in_dollar);
char    *handle_word(t_all *all, int in_dollar);
//finalization part
void    error(char *mess, t_all *all);
void	free_all_struct(t_all *all, int is_clear_env);
void    free_cmd_struct(t_cmd *lst_cmd);
void    free_redir_struct(t_redir *redir);
void    free_env_struct(t_env *lst_env);
void    free_args(t_args *lst_arg);


///////////////////	EXEC

///// processing.c
void    everyinit(t_msh *msh, int argc, char **argv, char **envp);
void	putstr(char *str);
///// processing.c

///// BUILTINS
void    env(t_env *env);
void    pwd(t_msh *msh);
void    cd(t_msh *msh, t_args *argv);
void	echo(t_msh *msh, t_args *argv);
void	export(t_msh *msh, t_args *argv);
///// BUILTINS


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
char	**split(char const *str, char c);
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
char	*fpath_tt(t_env *env, char *cmd, int i);
// char	*fpath_tt(char *cmd, int i); // find the absolute path of a cmd so we can execve it
///// EXEC.c

#endif
