#include "include/minishell.h"

void    everyinit(struct msh *msh, int argc, char **argv, char **envp)
{
	envinit(msh, envp);
	msh->pwd = malloc(sizeof(char) * 1000);
	getcwd(msh->pwd, 1000); // stock the pwd at the start, then we'll change it according to every directory change we do
	msh->argc = argc;
	msh->argv = argv;
}