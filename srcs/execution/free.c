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

void	wegotasplituation(struct spt x)
{
	int	i;

	i = -1;
	while (x.split[++i] && i <= x.op)
		free(x.split[i]);
	free(x.split);
}

void	fsplit(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
