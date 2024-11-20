/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:11:09 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/14 10:48:26 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "../../includes/signal.h"

static struct sigaction	init_sig_bs_logic(void);
static struct sigaction	init_sig_c_logic_parent(void);

void	init_signals(t_all *all)
{
	struct sigaction	act_bs;
	struct sigaction	act_c;

	act_bs = init_sig_bs_logic();
	if (sigaction(SIGQUIT, &act_bs, NULL) == -1)
		error("init_signals: sigaction error", all, SIGTERM);
	act_c = init_sig_c_logic_parent();
	if (sigaction(SIGINT, &act_c, NULL) == -1)
		error("init_signals: sigaction error", all, SIGTERM);
	return ;
}

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

static struct sigaction	init_sig_c_logic_parent(void)
{
	struct sigaction	act;
	sigset_t			set;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = sigint_hdl_parent;
	act.sa_flags = 0;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	act.sa_mask = set;
	return (act);
}

void	init_signals_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	return ;
}