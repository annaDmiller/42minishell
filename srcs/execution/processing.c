/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:21:58 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 08:22:00 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	everyinit(t_msh *msh, char **envp)
{
	msh->pwd= NULL;
	msh->exit = 0;
	msh->pwd = getcwd(NULL, 0); // stock the pwd at the start, cd(directory);
//		handle if !getcwd
	if (envp && envp[0])
		envinit(msh, envp, -1);
	else
		env_build(msh, -1);
}

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