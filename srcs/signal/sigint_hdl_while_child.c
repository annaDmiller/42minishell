#include "../../includes/minishell.h"

//file contains functions which handle SIGINT signal while pipe is running
//while we have child process running, if we press Ctrl+C both child and
//parent processes will catch the signal. After abrupting, child process
//will send the SIGINT signal to parent process. That's why we need ignoring
//logic for parent process while the child processes are running.

//function sets the temporary action for SIGINT signal -> ign_handler
//old_act - the information about previously set action for SIGINT (in init_signal.c)
//new_act - the information about newly set action for SIGINT (ign_handler)
struct sigaction	*sigint_ign_wait(t_all *all)
{
	struct sigaction	*old_act;
	struct sigaction	new_act;

	new_act.sa_handler = ign_handler;
	new_act.sa_flags = 0;
	old_act = (struct sigaction *) malloc(sizeof(struct sigaction));
	if (!old_act)
		error("ign_signal: malloc error\n", all);
	if (sigaction(SIGINT, &new_act, old_act) == -1)
		error("ign_signal: sigaction error\n", all);
	return (old_act);
}

//function allows to restore primary action for SIGINT
void	restore_sigint_hdl(t_all *all, struct sigaction *old_act)
{
	if (sigaction(SIGINT, old_act, NULL) == -1)
		error("restore_signal: sigaction error\n", all);
	free(old_act);
	return ;
}

//function which says for the parent process to print just a new line
void	ign_handler(int sig)
{
	printf("\n");
	(void) sig;
	return ;
}
