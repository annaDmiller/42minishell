/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:25:25 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 19:25:27 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

/// @brief for execve purpose // execve(path, argv, char **env) env = malloc(sizeof(char *) * l_envsize(msh->env))
/// @return return the size of the environment
int	l_envsize(t_env *env)
{
	t_env	*tmp;
	int		l;

	l = 0;
	tmp = env;
	while (tmp && ++l > 0)
		tmp = tmp->next;
	return (l);
}

/// @brief for execve purpose // execve(path, char ** argv,env) argv = malloc(sizeof(char *) * l_argsize(cmd->argv))
/// @return return how much arguments the cmd has
int	l_argsize(t_args *argv)
{
	t_args	*tmp;
	int		l;

	l = 0;
	tmp = argv;
	while (tmp && ++l > 0)
		tmp = tmp->next;
	return (l);
}
