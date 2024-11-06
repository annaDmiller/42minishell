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

/// @brief freeing whats needed to be freed in child process
void	free_exit(t_all *all, t_msh *msh, int t)
{
	free(msh->pwd);
	free(msh->data);
	freenv(msh->env);
	if (!t)
		return ;
	free_all_struct(all, 1);
}

/// @brief free the whole env linked list
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

/// @brief free only one env variable
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

/// @brief free a char **
void	fsplit(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
