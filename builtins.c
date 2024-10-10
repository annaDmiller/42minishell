/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:31:46 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/10 14:08:35 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void    pwd(t_msh *msh)
{	
	printf("%s\n", msh->pwd);
}

void	echo(t_msh *msh, char *str)
{
	putstrfd(str, STDOUT_FILENO);
	// if (!cmd_line->next || !(tstrcmp(cmd_line->next, "-n") == 0)) // check if there is echo -n or not 
		// write(STDOUT_FILENO, "\n", 1);
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
