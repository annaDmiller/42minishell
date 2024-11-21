/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/20 22:55:18 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;

	cmd = all->lst_cmd;
	if (!cmd)
		return ;
	if (!cmd->prev && !cmd->next)
	{
		_execmd(all, msh, cmd, SOLO);
		if (cmd->name && !tstrcmp(cmd->name, "exit") && g_sig)
			return ;
	}
	else
	{
		msh->_stdin_save = dup(STDIN_FILENO);
		tpipe(all, msh, cmd);
		dup2(msh->_stdin_save, STDIN_FILENO);
		close(msh->_stdin_save);
	}
	while (wait(NULL) != -1)
		continue ;
}
