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

extern volatile int g_sig;
//list_logic
t_cmd   *cmd_new(t_all *all);
void    cmd_add_el_back(t_all *all, t_cmd *new_el);
t_cmd   *cmd_last_el(t_all *all);
t_args   *arg_new(t_all *all);
void    arg_add_el_back(t_cmd *last_cmd, t_args *new_el);
t_args   *arg_last_el(t_cmd *last_cmd);
//main part
char    *print_prompt(t_all *all);
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
char    *handle_dollar(t_all *all, t_cmd *cmd, char car);
char    *handle_redir(t_all *all, t_cmd *cmd);
char *read_addr(t_all *all, t_cmd *cmd);
char    *handle_input(t_all *all, t_cmd *cmd);
char    *handle_output(t_all *all, t_cmd *cmd);
char    *handle_quotes(t_all *all, t_cmd *cmd);
char    *handle_word(t_all *all, t_cmd *cmd, int in_dollar);
//finalization part
void    error(char *mess, t_all *all);
void    free_all_struct(t_all *all);
void    free_cmd_struct(t_cmd *lst_cmd);
void    free_redir_struct(t_redir *redir);
void    free_env_struct(t_env *lst_env);
void    free_args(t_args *lst_arg);
#endif
