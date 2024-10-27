/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:33:18 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/23 16:33:20 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	tpipe(t_msh *msh, t_cmd *cmd)
{
	int	tfd;

	tfd = 0;
	if (pipe(cmd->redir->pipe_fd) == -1)
		return ;// handle error
	start(msh, cmd);
	cmd = cmd->next;
	fprintf(stderr, "START\n");
	while (cmd && cmd->next)
	{
		mid(msh, cmd);
		cmd = cmd->next;
		fprintf(stderr, "MID\n");
		sleep(1);
	}
	if (cmd)
		end(msh, cmd);
	fprintf(stderr, "END\n");
	// fprintf(stderr, "____________________________________________________\n\n");
	(void)tfd;
}

/// ON ECRIT DANS PIPE_FD[1]
/// ON LIT DANS PIPE_FD[0]

void	start(t_msh *msh, t_cmd *cmd)
{
	pid_t	tpid;

	(void)msh;
	(void)cmd;
	(void)tpid;
}

void	mid(t_msh *msh, t_cmd *cmd)
{
	pid_t	tpid;

	(void)msh;
	(void)cmd;
	(void)tpid;
}

void	end(t_msh *msh, t_cmd *cmd)
{
	pid_t	tpid;

	(void)msh;
	(void)cmd;
	(void)tpid;
}
