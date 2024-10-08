/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 18:41:33 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/08 18:41:44 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void	envinit(struct msh *msh, char **envp)
{
	t_env	*env;
	t_env	*nvx;
	t_env	*head;
	int			i;

	i = -1;
	nvx = NULL;
	env = (t_env *)malloc(sizeof(t_env));
	if (!env)
		return ; // error handling
	if (!envp[0])
	{
		env->status = -1;
		env->id = 0;
		env->name = NULL;
		env->var = NULL;
		env->next = NULL;
		return ; // error handling
	}
	while (envp[++i])
	{
		nvx = (t_env *)malloc(sizeof(t_env));
		if (!nvx) // return i to know how much node we have to free
			return ;
		nvx->status = 1;
		nvx->id = i + 1;
		nvx->next = NULL;
		nvx->name = env_varname(envp[i]); // function to stock the name of the variable
		// printf("%s\n", nvx->name);
		nvx->var = env_var(envp[i]); // function to stock the content of the env variable
		env->next = nvx;
		env = nvx;
		if (i == 0)
			head = env;
	}
	msh->env = head;
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