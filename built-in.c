/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:31:46 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 08:21:06 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void    pwd(t_msh *msh)
{	
	printf("%s\n", msh->pwd);
}

void    env(t_msh *msh)
{
	t_env	*tmp;

	tmp = msh->env;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
}
