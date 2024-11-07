#include "../../includes/minishell.h"

struct sigaction	*sigint_ign_wait(t_all *all)
{
	struct sigaction	*old_act;
	struct sigaction	new_act;

	new_act.sa_handler = ign_handler;
	new_act.sa_flags = 0;
	old_act = (struct sigaction *) malloc(sizeof(struct sigaction));
	if (!old_act)
		error("ign_signal: malloc error", all, SIGTERM);
	if (sigaction(SIGINT, &new_act, old_act) == -1)
		error("ign_signal: sigaction error", all, SIGTERM);
	return (old_act);
}

void	restore_sigint_hdl(t_all *all, struct sigaction *old_act)
{
	if (sigaction(SIGINT, old_act, NULL) == -1)
		error("restore_signal: sigaction error", all, SIGTERM);
	free(old_act);
	return ;
}

void	ign_handler(int sig)
{
	printf("\n");
	(void) sig;
	return ;
}
