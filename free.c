#include "include/minishell.h"



void	freestr(char *str)
{
	free(str);
}

void	freecmdline(t_args *arg)
{
	t_args	*tmp;

	tmp = arg;
	while (arg)
	{
		tmp = arg;
		arg = arg->next;
		free(tmp);
	}
}

void	freenv(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->var);
		free(tmp);
	}
}