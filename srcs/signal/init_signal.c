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
#include "../../includes/signal.h"

static struct sigaction	init_sig_bs_logic(void);
static struct sigaction	init_sig_c_logic_parent(void);
static struct sigaction	init_sig_c_logic_child(void);

void	init_signals(t_all *all, char proc)
{
	struct sigaction	act_bs;
	struct sigaction	act_c;

	act_bs = init_sig_bs_logic();
	if (sigaction(SIGQUIT, &act_bs, NULL) == -1)
		error("init_signals: sigaction error", all, SIGTERM);
	if (proc == 'p')
		act_c = init_sig_c_logic_parent();
	else if (proc == 'c')
		act_c = init_sig_c_logic_child();
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

static struct sigaction	init_sig_c_logic_child(void)
{
		struct sigaction	act;
	sigset_t			set;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = sigint_hdl_child;
	act.sa_flags = 0;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	act.sa_mask = set;
	return (act);	
}
