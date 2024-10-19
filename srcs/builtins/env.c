/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:24 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:25 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	envinit(t_msh *msh, char **envp, int i)
{
	t_env	*tmp;

	msh->env = NULL;
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
		tmp->name = env_varname(envp[i]);
 		tmp->var = env_var(envp[i]);
 		tmp->id = i + 1;
		tmp->next = NULL;
	}
}

void	env_build(t_msh *msh, int i)
{
	t_env	*tmp;

	while (++i < 3)
	{
		if (msh->env == NULL)
		{
			msh->env = (t_env *)malloc(sizeof(t_env));
			if (msh->env == NULL)
				return ;
			tmp = msh->env;
		}
		else if (msh->env)
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			if (tmp->next == NULL)
				return ; // error malloc
			tmp = tmp->next;
		}
		if (i == 0)
		{
			tmp->name = env_varname("PWD");
			tmp->var = tstrdup(msh->pwd);
			tmp->id = i + 1;
			tmp->next = NULL;
		}
		if (i == 1)
		{
			tmp->name = env_varname("SHLVL");
			tmp->var = env_var("SHLVL=1");
			tmp->id = i + 1;
			tmp->next = NULL;
		}
		if (i == 2)
		{
			tmp->name = env_varname("_");
			tmp->var = env_var("_=/usr/bin/env");
			tmp->id = i + 1;
			tmp->next = NULL;
		}
	}
	(void)msh;
	(void)tmp;
}


/// @brief Display the environnement		variable=value
/// // //   if there is no value, it just print variable=""
/// @param t_env *env 
void    env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	if (!tmp)
		printf("PROUTPROUTPROUT\n\n\n");
	while (tmp)
	{
		if (tmp->var)
			printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
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
	if (d == -1)
		return (NULL);
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
