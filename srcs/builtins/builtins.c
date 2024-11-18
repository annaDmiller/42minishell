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

int	exec_buitin(t_msh *msh, t_cmd *cmd)
{
	if (!tstrcmp(cmd->name, "export"))
		return (export(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "pwd"))
		return (pwd(msh));
	else if (!tstrcmp(cmd->name, "echo"))
	{
		msh->exit = EXIT_SUCCESS;
		return (echo(cmd->argv));
	}
	else if (!tstrcmp(cmd->name, "cd"))
		return (cd(msh, cmd->argv, NULL, 0));
	else if (!tstrcmp(cmd->name, "env"))
		return (env(msh->env));
	else if (!tstrcmp(cmd->name, "unset"))
	{
		msh->exit = EXIT_SUCCESS;
		return (unset(msh, cmd->argv));
	}
	else if (!tstrcmp(cmd->name, "exit"))
		return (texit(msh, cmd, cmd->argv));
	return (0);
}

int	is_a_buitin(char *cmd_name)
{
	if (!tstrcmp(cmd_name, "export"))
		return (1);
	else if (!tstrcmp(cmd_name, "pwd"))
		return (1);
	else if (!tstrcmp(cmd_name, "echo"))
		return (1);
	else if (!tstrcmp(cmd_name, "cd"))
		return (1);
	else if (!tstrcmp(cmd_name, "env"))
		return (1);
	else if (!tstrcmp(cmd_name, "unset"))
		return (1);
	else if (!tstrcmp(cmd_name, "exit"))
		return (1);
	return (0);
}