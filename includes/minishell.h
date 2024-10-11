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

char    *print_prompt(void);
void    parse_line(t_all *all);
void    free_lst(t_cmd *lst_cmd);
int is_empty_line(char *cmd_line);
int  find_end_cmd(char   *cmd_line);
t_cmd   *cmd_new(t_all *all);
int  is_white_space(char car);
void    add_cmd(t_all *all);
#endif
