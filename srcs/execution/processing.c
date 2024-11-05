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

void	everyinit(t_msh *msh, char **envp)
{
	msh->pwd = NULL;
	msh->exit = 0;
	msh->pipe_fd[0] = -2;
	msh->pipe_fd[1] = -2;
	msh->_stdin_save = -2;
	msh->have_to_exit = 0;
	msh->pwd = getcwd(NULL, 0);
	if (envp && envp[0])
		envinit(msh, envp, -1);
	else
		env_build(msh, -1);
	msh->data = malloc(sizeof(t_execve));
	if (!msh->data)
	{
		freenv(msh->env);
		exit(33);
	}
	msh->data->path = NULL;
	msh->data->argv = NULL;
	msh->data->envp = NULL;
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
				return ;
			tmp = msh->env;
		}
		else
		{
			tmp->next = (t_env *)malloc(sizeof(t_env));
			if (tmp->next == NULL)
				return ;
			tmp = tmp->next;
		}
		tmp->name = env_varname(envp[i]);
		tmp->var = env_var(envp[i]);
		tmp->id = i + 1;
		tmp->next = NULL;
	}
}

// void	env_build(t_msh *msh, int i)
// {
// 	t_env	*tmp;

// 	msh->env = NULL;
// 	while (++i < 3)
// 	{
// 		if (msh->env == NULL)
// 		{
// 			msh->env = (t_env *)malloc(sizeof(t_env));
// 			if (msh->env == NULL)
// 				return ;
// 			tmp = msh->env;
// 		}
// 		if (!tmp->next)
// 		{
// 			tmp->next = (t_env *)malloc(sizeof(t_env));
// 			if (tmp->next == NULL)
// 				return ; // error malloc
// 			tmp = tmp->next;
// 		}
// 		if (i == 0)
// 		{
// 			tmp->name = env_varname("PWD");
// 			tmp->var = tstrdup(msh->pwd);
// 		}
// 		if (i == 1)
// 		{
// 			tmp->name = env_varname("SHLVL");
// 			tmp->var = env_var("SHLVL=1");
// 		}
// 		if (i == 2)
// 		{
// 			tmp->name = env_varname("_");
// 			tmp->var = env_var("_=/usr/bin/env");
// 		}
// 		tmp->id = i + 1;
// 		tmp->next = NULL;
// 	}
// 	(void)msh;
// 	(void)tmp;
// }
// void	env_build(t_msh *msh, int i)
// {
// 	t_env	*tmp;

// 	msh->env = NULL;
// 	while (++i < 3)
// 	{
// 		if (msh->env == NULL)
// 		{
// 			msh->env = malloc(sizeof(t_env));
// 			if (!msh->env)
// 				return ;//handle error
// 		}
// 		printf("%d\n", i);
// 		if (i == 0)
// 		{
// 			msh->env->name = env_varname("PWD");
// 			msh->env->var = tstrdup(msh->pwd);
// 			tmp = msh->env;
// 		}
// 		else if (i == 1)
// 		{
// 			msh->env->name = env_varname("SHLVL");
// 			msh->env->var = env_var("SHLVL=1");
// 		}
// 		else if (i == 2)
// 		{
// 			msh->env->name = env_varname("_");
// 			msh->env->var = env_var("_=/usr/bin/env");
// 		}
// 		msh->env->id = i + 1;
// 		msh->env->next = NULL;
// 		msh->env = msh->env->next;
// 	}
// 	msh->env = tmp;
// 	(void)msh;
// 	(void)tmp;
// }
/// @brief need to understand that
static void	add_to_env(t_env **env, int i, char *env_name, char *env_var)
{
	t_env	*tmp;
	t_env	*new;

	tmp = *env;
	new = malloc(sizeof(t_env));
	new->id = i + 1;
	new->name = env_varname(env_name);
	new->var = tstrdup(env_var);
	new->next = NULL;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	else
		*env = new;
}

void	env_build(t_msh *msh, int i)
{
	msh->env = NULL;
	while (++i < 3)
	{
		if (i == 0)
			add_to_env(&msh->env, i, "PWD", msh->pwd);
		else if (i == 1)
			add_to_env(&msh->env, i, "SHLVL", "1");
		else if (i == 2)
			add_to_env(&msh->env, i, "_", "/usr/bin/env");
	}
}
