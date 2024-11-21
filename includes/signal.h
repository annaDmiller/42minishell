/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:41:44 by amelniko          #+#    #+#             */
/*   Updated: 2024/11/14 10:42:48 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNAL_H
# define SIGNAL_H
# include "minishell.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <limits.h>
# define _GNU_SOURCE

//signals
void				init_signals(t_all *all);
void				sigint_hdl_parent(int sig);
void				sigint_hdl_child(int sig);
struct sigaction	*sigint_ign_wait(t_all *all, int is_child);
struct sigaction	*sigquit_ign_def(t_all *all);
void				restore_sigint_hdl(t_all *all, struct sigaction *old_act);
void				restore_sigquit_hdl(t_all *all, struct sigaction *old_act);
void				ign_handler(int sig);
void				init_signals_child(void);
#endif
