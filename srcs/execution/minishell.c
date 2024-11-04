/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/11 00:53:24 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	wgas(char *str, int ext)
{
	printf("%s\n", str);
	exit(ext);
}

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;

	cmd = all->lst_cmd;
	if (!cmd || !cmd->name)
		return ;
	else if (!cmd->prev && !cmd->next)
	{
		_execmd(all, msh, cmd, SOLO);
		if (!tstrcmp(cmd->name, "exit") && g_sig)
			return ;
	}
	else
		tpipe(all, msh, cmd);
	while (wait(NULL) != -1)
		continue ;
}
