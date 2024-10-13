#include "../include/minishell.h"

// bash-5.1$ env -i unset PATH
// env: ‘unset’: No such file or directory
// bash-5.1$
char	*setup_name(char *str)
{
	char    *name;
	int		i;
	int		r;

	i = 0;
	r = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	name[i] = '\0';
	while (--i >= 0)
		name[i] = str[i];
	return (name);
}

/// @brief unset can take multiple arguments, and unset them one by one
/// it'll try to unset every argumenth if it exists // never will display an error message
/// @retval == 0 // All name operands were successfully unset.
/// @retval > 0  // At least one name could not be unset.
void    unset(t_msh *msh, t_args *argv)
{
	// ideally doubly linked list ill go previous but dk how to implement it
	t_env   *node;
	t_env   *tmp;
	char	*name;
	// int             i;
	while(argv)
	{
		tmp = msh->env;	
		name = setup_name(argv->arg);
		node = env_retrieve_var(msh->env, name); // pcque le nom de la variable est export nomdelavariable
		if (!name || !node)
			freestr(name);
		else
			while (tmp && tmp->next->id != node->id) // je parcours ma liste avec tmp, lorsque le prochaine correspond a la var que je veux enlever je m'arrete
				tmp = tmp->next;
		if (!node->next) // if the var I want to unset is the last one in the list
		{
			free(node); // I just free it
			tmp->next = NULL; // and set ->next of the one before him to NULL
		}
		else
		{
			tmp->next = node->next;
			freestr(name);
			free(node->name);
			free(node->var);
			free(node);
		}
		argv = argv->next;
		freestr(name);
	}
}
