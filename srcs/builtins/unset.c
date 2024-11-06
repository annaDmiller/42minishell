/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:06 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:09 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

// bash-5.1$ env -i unset PATH
// env: ‘unset’: No such file or directory
// bash-5.1$
int	unset(t_msh *msh, t_args *argv)
{
	t_env	*save;
	t_env	*tmp;
	char	*name;

	while (argv)
	{
		tmp = msh->env;
		save = NULL;
		name = setup_name(argv->arg);
		if (name && env_retrieve_var(msh->env, name)) // if the argv exist in the env 
			unset_and_link(msh, tmp, save, name);
		if (name)
			free(name);
		argv = argv->next;
	}
	msh->exit = 0; // no matter what the exit code will be 0
	return (1);
}

void	unset_and_link(t_msh *msh, t_env *tmp, t_env *save, char *name)
{
	while (tmp)
	{
		if (tmp->next)
			if (!tstrcmp(name, tmp->next->name)) // if we found the previous env variable of the variable we want to unset we break
				break ;
		tmp = tmp->next;
	}
	if (tmp && tmp->next && !tmp->next->next) // if its the last variable in the env linked list
	{
		freenvar(tmp->next); // unset the one we want to unset
		tmp->next = NULL; // and set the onebeforeit->next to NULL
	}
	else if (tmp && tmp->next && tmp->next->next) // if we wanna unset in the middle of the linked list
	{
		save = tmp->next->next; // we save the one after it 
		freenvar(tmp->next); // unset the one we want to unset
		tmp->next = save; // link the one before it with the one after it
	}
	if (!tmp && msh->env && msh->env->next && !tstrcmp(msh->env->name, name)) // if we havent find any name as the one we wanna unset in the first while loop
	{								// it means we wanna unset the first variable in msh->env
		save = msh->env->next; // we save the one after it 
		freenvar(msh->env); // unset the first env variable
		msh->env = save; // set msh->env to save
	}
}

char	*setup_name(char *str)
{
	char	*name;
	int		i;

	i = 0;
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

/// @brief reset '$_' variable with the last command line entered
void	_var(t_all *all, t_msh *msh)
{
	t_env	*var;
	char	*str;
	char	*_prefix;

	var = env_retrieve_var(msh->env, "_");
	if (var && all && all->line)
	{
		free(var->var);
		_prefix = malloc(sizeof(char) * 3);
		if (!_prefix)
			return ;
		_prefix[0] = '_';
		_prefix[1] = '=';
		_prefix[2] = '\0';
		str = tjoin(_prefix, all->line);
		var->var = env_var(str);
		free(str);
	}
}
