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

/// @brief function that will execute a builtin if the cmd->name is one of the builtin that had to be done
/// @return if a builtin is executed it will return 1, then if (is_a_buitin(msh, cmd)) is verified
int	is_a_buitin(t_msh *msh, t_cmd *cmd)
{
	if (!tstrcmp(cmd->name, "export"))
		return (export(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "pwd"))
		return (pwd(msh));
	else if (!tstrcmp(cmd->name, "echo"))
		return (echo(cmd->argv));
	else if (!tstrcmp(cmd->name, "cd"))
		return (cd(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "env"))
		return (env(msh->env));
	else if (!tstrcmp(cmd->name, "unset"))
		return (unset(msh, cmd->argv));
	else if (!tstrcmp(cmd->name, "exit"))
		return (texit(msh, cmd, cmd->argv));
	return (0); // return 0, cause the cmd->name wasnt any builtin	(!is_a_buitin(msh, cmd))
}
