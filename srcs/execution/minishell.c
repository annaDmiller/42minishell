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

static	void	test(int tt)
{
	int	i;

	i = -1;

	(void)i;
	(void)tt;
}

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	// if (all->lst_cmd->redir)
	cmd = all->lst_cmd;
	if (cmd->redir && cmd->redir->is_pipe == 'y')
	{
		// printf("JE SUIS UN PIPE");
		// handle le pipe
		return ;
	}
	if (!cmd->redir)
		printf("IL N'Y A PAS DE REDIRECTION");
	one_exec(msh, all->lst_cmd);
	test(0);
	(void)i;
	(void)msh;
	(void)all;
}
