/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:31:46 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 14:04:09 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	is_a_buitin(t_msh *msh, t_cmd *cmd)
{
	if (!tstrcmp(cmd->name, "export"))
		export(msh, cmd->argv);
	else if (!tstrcmp(cmd->name, "pwd"))
		printf("%s\n", msh->pwd);
	else if (!tstrcmp(cmd->name, "echo"))
		echo(msh, cmd->argv);
	else if (!tstrcmp(cmd->name, "cd"))
		cd(msh, cmd->argv);
	else if (!tstrcmp(cmd->name, "env"))
		env(msh->env);
	else if (!tstrcmp(cmd->name, "unset"))
		unset(msh, cmd->argv);
	else if (!tstrcmp(cmd->name, "exit"))
		texit(msh, cmd->argv);
	else
		return (0);
	return (2);
}
