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

void	wgas(char *str, int ext)
{
	fprintf(stderr, "%s\n", str);
	exit(ext);
}

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = all->lst_cmd;
	if (!cmd->redir)
	{
		// fprintf(stderr, "__________________________SINGLE__________________________\n\n");
		_execmd(msh, cmd);
	}
	else if (cmd->redir && cmd->redir->is_pipe == 'y')
	{
		// fprintf(stderr, "__________________________PIPE__________________________\n\n");
		tpipe(msh, cmd);
		return ;
	}
	test(0);
	(void)i;
}
