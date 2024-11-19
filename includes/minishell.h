/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:16:13 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/21 16:15:13 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include "../libft/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# include <dirent.h>
# include "structures.h"
# include "signal.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

# define PROMPT "minishell> "
# define _GNU_SOURCE

extern volatile int	g_sig;

//list_logic
t_cmd	*cmd_new(t_all *all);
void	cmd_add_el_back(t_all *all, t_cmd *new_el);
t_cmd	*cmd_last_el(t_all *all);
t_args	*arg_new(t_all *all);
void	arg_add_el_back(t_cmd *last_cmd, t_args *new_el);
t_args	*arg_last_el(t_cmd *last_cmd);
//main part
int		validate_line(t_all *all);
t_all	*init_all_struct(t_all *all, t_msh *msh);
//parsing main
void	parse_line(t_all *all);
void	parse_cmd(t_all *all, t_cmd *last);
void	add_arg(t_all *all, t_cmd *last, char **str);
void	add_str_to_cmd(t_all *all, t_cmd *cmd, char **str);
void	init_redir(t_redir *redir);
//parsing utils
int		is_white_space(char car);
int		is_empty_line(char *cmd_line);
int		is_quote(char car);
int		is_redir(char car);
//parsing main functions
char	*handle_dollar(t_all *all, t_cmd *cmd);
char    *parse_env_val(t_all *all, char **env_val, t_cmd *cmd);
char	*handle_redir(t_all *all, t_cmd *cmd);
char	*read_addr(t_all *all, t_cmd *cmd);
void	handle_input(t_all *all, t_cmd *cmd);
int		input_from_stdin(t_all *all, t_cmd *cmd);
void	handle_output(t_all *all, t_cmd *cmd);
char	*handle_quotes(t_all *all, t_cmd *cmd, int in_dollar);
char	*handle_word(t_all *all, int in_dollar, int in_redir);
//finalization part
void	error(char *mess, t_all *all, int sig);
void	free_all_struct(t_all *all, int is_clear_env);
void	free_cmd_struct(t_cmd *lst_cmd);
void	free_redir_struct(t_redir *redir);
void	free_args(t_args *lst_arg);

void	init_redir(t_redir *redir);

int		input_from_stdin(t_all *all, t_cmd *cmd);
int		read_from_stdin(t_all *all, t_cmd *cmd);
int		hdc_writing(t_all *all, t_cmd *cmd);

///////////////////	EXEC
void	minishell(t_all *all, t_msh *msh);

///// PROCESSING.c
void	everyinit(t_msh *msh, char **envp, int argc, char **argv);
void	envinit(t_msh *msh, char **env, int i);
void	env_build(t_msh *msh, int i);
///// PROCESSING.c

///// EXECUTION
int		_execmd(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos);
int		cmd_check(t_all *all, t_msh *msh, t_cmd *cmd);

int		set_execve(t_msh *msh, t_cmd *cmd);
char	**setup_env(t_env *env);
char	**setup_args(char *name, t_args *argv);
char	*fpath(t_env *env, char *cmd, int i);

void	tpipe(t_all *all, t_msh *msh, t_cmd *cmd);
void	chromakopia(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos);
///// EXECUTION

///// BUILTINS
int		exec_buitin(t_msh *msh, t_cmd *cmd);
int		is_a_buitin(char *cmd_name);

int		cd(t_msh *msh, t_args *argv, char *str, int tzy);
int		valid_cd(t_msh *msh, t_args *argv);
int		wave(t_msh *msh, char *str);

int		echo(t_args *argv);
void	putstr(char *str);

int		env(t_env *env);
char	*env_var(char *str);
char	*env_varname(char *str);
t_env	*env_retrieve_var(t_env *env, char *str);
t_env	*env_retrieve_var(t_env *env, char *str);

int		texit(t_msh *msh, t_cmd *cmd, t_args *argv);

int		export(t_msh *msh, t_args *argv);
void	export_no_opt(t_msh *msh);
void	export_def(t_msh *msh, t_args *argv);

int		pwd(t_msh *msh);

int		unset(t_msh *msh, t_args *argv);
void	unset_and_link(t_msh *msh, t_env *tmp, t_env *save, char *name);
char	*setup_name(char *str);
///// BUILTINS

///// FREE.c
void	free_exit(t_all *all, t_msh *msh, int t); // free in child process
void	freenv(t_env *env); // free env linked list 
void	freenvar(t_env *var); // free only one environment variable
void	fsplit(char **str); // free a char **
///// FREE.c

///// TLIB.c
char	*tstrdup(char *src);
char	*tjoin(char *str, char *add);
int		tstrlen(char *str);
int		tstrcmp(char *str, char *cmp);
int		dir_check(char *file);
///// TLIB.c

///// TLIST.c
int		l_envsize(t_env *env);
int		l_argsize(t_args *argv);
///// TLIST.c

#endif
