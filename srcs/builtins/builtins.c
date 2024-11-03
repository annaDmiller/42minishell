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
		return (export(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "pwd"))
		return (pwd(msh));
	else if (!tstrcmp(cmd->name, "echo"))
		return (echo(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "cd"))
		return (cd(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "env"))
		return (env(msh->env));
	else if (!tstrcmp(cmd->name, "unset"))
		return (unset(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "exit"))
		return (texit(msh, cmd, cmd->argv));
	return (0);
}
