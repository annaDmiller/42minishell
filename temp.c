/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:53:18 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 15:53:21 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void	echo(t_msh *msh, t_cmd *cmd)
{
	// while ()
	// putstrfd(str, STDOUT_FILENO);
	// if (!cmd_line->next || !(tstrcmp(cmd_line->next, "-n") == 0)) // check if there is echo -n or not 
		// write(STDOUT_FILENO, "\n", 1);
	(void)msh;
	(void)cmd;
}

char	*expand(t_msh *msh, char *str)
{
	return (env_retrieve_var(msh->env, str)->var);
}
