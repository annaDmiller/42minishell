#include "include/minishell.h"

// idealement en argument un pointeur sur le noeud $USER dans la ligne de commande
char	*expand(struct msh *msh, char *str)
{
	t_env	*tmp;

	tmp = env_retrieve_var(msh->env, str);
	tmp = env_retrieve_var(msh->env, "DISPLAY");
	tmp = env_retrieve_var(msh->env, "USER");
	// if (!tmp)
// 		it doesn't exist, handle what to return
	return (tmp->var);
}