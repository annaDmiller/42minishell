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
		if (name && env_retrieve_var(msh->env, name))
			unset_and_link(msh, tmp, save, name);
		if (name)
			free(name);
		argv = argv->next;
	}
	msh->exit = 0;
	return (1);
}

void	unset_and_link(t_msh *msh, t_env *tmp, t_env *save, char *name)
{
	while (tmp)
	{
		if (tmp->next)
			if (!tstrcmp(name, tmp->next->name))
				break ;
		tmp = tmp->next;
	}
	if (tmp && tmp->next && !tmp->next->next)
	{
		freenvar(tmp->next);
		tmp->next = NULL;
	}
	else if (tmp && tmp->next && tmp->next->next)
	{
		save = tmp->next->next;
		freenvar(tmp->next);
		tmp->next = save;
	}
	if (!tmp && msh->env && msh->env->next && !tstrcmp(msh->env->name, name))
	{
		save = msh->env->next;
		freenvar(msh->env);
		msh->env = save;
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
