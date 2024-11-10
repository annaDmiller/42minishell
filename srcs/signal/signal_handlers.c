#include "../../includes/minishell.h"
#include "../../includes/signal.h"

void	sigint_hdl_parent(int sig)
{
	g_sig = sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	sigint_hdl_child(int sig)
{
	g_sig = sig;
	return ;
}

void	ign_handler(int sig)
{
	g_sig = sig;
	printf("\n");
	return ;
}
