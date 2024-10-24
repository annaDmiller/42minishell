#include "../../includes/minishell.h"

static struct sigaction	init_sig_bs_logic(void);
static struct sigaction	init_sig_c_logic(void);

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

void	sigint_hdl(int sig)
{
	g_sig = sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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
