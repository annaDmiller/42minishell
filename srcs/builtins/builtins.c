/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:31:46 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/21 00:55:35 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	exec_buitin(t_msh *msh, t_cmd *cmd)
{
	if (!tstrcmp(cmd->name, "export"))
	{
		if (!cmd->argv)
			export_no_opt(msh);
		else
			export(msh, cmd->argv);
		return (1);
	}
	else if (!tstrcmp(cmd->name, "pwd"))
		return (pwd(msh));
	else if (!tstrcmp(cmd->name, "echo"))
	{
		msh->exit = 0;
		return (echo(msh, cmd->argv, 0, 1));
	}
	else if (!tstrcmp(cmd->name, "cd"))
		return (cd(msh, cmd->argv, 0));
	else if (!tstrcmp(cmd->name, "env"))
		return (env(msh->env));
	else if (!tstrcmp(cmd->name, "unset"))
		return (unset(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "exit"))
		return (texit(msh, cmd, cmd->argv));
	return (0);
}
