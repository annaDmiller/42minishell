/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:41:33 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 15:52:41 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void	envinit(t_msh *msh, char **envp, int i)
{
	t_env	*tmp;

	msh->env = NULL;
	if (!envp[0])
		return ; // error handling
	while (envp[++i])
	{
		if (msh->env == NULL)
		{
			msh->env = (t_env *)malloc(sizeof(t_env));
			if (msh->env == NULL)
				return ; // error malloc
			tmp = msh->env;
		}
		else
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			if (tmp->next == NULL)
				return ; // error malloc
			tmp = tmp->next;
		}
		tmp->name = env_varname(envp[i]); // function to stock the name of the variable
 		tmp->var = env_var(envp[i]); // function to stock the content of the env variable
 		tmp->id = i + 1; // index idk for what purpose yet
		tmp->next = NULL;
	}
}

char	*env_var(char *str)
{
	char	*var;
	int		i;
	int		d;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	d = tstrlen(str) - i;
	var = (char *)malloc(sizeof(char) * d + 1);
	if (!var)
		return (NULL); // error handling
	var[d] = '\0';
	while (--d >= 0)
		var[d] = str[d + i];
	return (var);
}

char	*env_varname(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=') // i will equal length of the name variable without its content
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL); // error handling
	name[i] = '\0';
	while (--i >= 0)
		name[i] = str[i];
	return (name);
}

t_env	*env_retrieve_var(t_env *env, char *str)
{
	t_env	*tmp;
	int		i;
	
	tmp = env;
	if (!str)
		return (NULL);
	while (tmp)
	{
		i = -1;
		while (tmp->name[++i] && str[i])
			if (tmp->name[i] != str[i])
				break;
		if (!tmp->name[i] && !str[i]) // if we arrived at the end without breaking before, words are the same
			return (tmp);
		tmp = tmp->next;		
	}
	return (NULL);
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
