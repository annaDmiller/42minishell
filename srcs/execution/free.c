/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 22:09:43 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 22:09:46 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	free_exit(t_all *all, t_msh *msh, int t)
{
	if (msh->pwd)
		free(msh->pwd);
	if (msh->home)
		free(msh->home);
	free(msh->data);
	freenv(msh->env);
	if (!t)
		return ;
	rl_clear_history();
	fds(all);
	free_all_struct(all, 1);
}

void	freenv(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (env)
	{
		tmp = env;
		env = env->next;
		if (tmp->name)
			free(tmp->name);
		if (tmp->var)
			free(tmp->var);
		if (tmp)
			free(tmp);
	}
}

void	freenvar(t_env *var)
{
	if (var)
	{
		if (var->var)
			free(var->var);
		if (var->name)
			free(var->name);
		if (var)
			free(var);
	}
}

void	fsplit(char **str)
{
	int	i;

	i = -1;
	if (str)
	{
		while (str[++i])
			free(str[i]);
		free(str);
	}
}
