#include "../../includes/minishell.h"

static struct	sigaction	init_sig_logic(void);

void	manage_signals(void)
{
	struct sigaction	act;

	act = init_sig_logic();
	if (sigaction(SIGQUIT, &act, NULL) == -1
		|| sigaction(SIGINT, &act, NULL) == -1)
		exit(EXIT_FAILURE);
	return ;
}

void	hdl(int sig)
{
	g_sig = sig;
	return ;
}

static struct sigaction	init_sig_logic(void)
{
	struct sigaction	act;
	sigset_t			set;

	ft_memset(&act, 0, sizeof(act));
	act.sa_sigaction = hdl;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	act.sa_mask = set;
	return (act);
}
