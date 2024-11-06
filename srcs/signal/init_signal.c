/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:11:09 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/30 21:11:12 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

//file contains functions for primary initialization of signals
static struct sigaction	init_sig_bs_logic(void);
static struct sigaction	init_sig_c_logic(void);

//main function for primary initialization of signals
void	init_signals(t_all *all)
{
	struct sigaction	act_bs;
	struct sigaction	act_c;

	act_bs = init_sig_bs_logic();
	act_c = init_sig_c_logic();
	if (sigaction(SIGQUIT, &act_bs, NULL) == -1)
		error("init_signals: sigaction error\n", all);
	if (sigaction(SIGINT, &act_c, NULL) == -1)
		error("init_signals: sigaction error\n", all);
	return ;
}

//handler for SIGINT which allows to move to another prompt of readline
//rl_replace_line cleans the buffer of readline
//rl_on_new_line moves to new line
//rl_redisplay displays the prompt once more
void	sigint_hdl(int sig)
{
	g_sig = sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

//function which defines the actions for Ctrl+\ signal -> IGNORE
//sa_flags = 0 means that signal abrupts current process
static struct sigaction	init_sig_bs_logic(void)
{
	struct sigaction	act;
	sigset_t			set;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = SIG_IGN;
	act.sa_flags = 0;
	sigemptyset(&set);
	sigaddset(&set, SIGQUIT);
	act.sa_mask = set;
	return (act);
}

//function which defines the actions for Ctrl+C signal -> sigint_hdl
//sa_flags = 0 means that signal abrupts current process
static struct sigaction	init_sig_c_logic(void)
{
	struct sigaction	act;
	sigset_t			set;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = sigint_hdl;
	act.sa_flags = 0;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	act.sa_mask = set;
	return (act);
}
