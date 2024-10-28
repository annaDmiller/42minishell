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

void	tpipe(t_all *all, t_msh *msh, t_cmd *cmd)
{
	int	tfd;

	tfd = 0;
	if (pipe(cmd->redir->pipe_fd) == -1)
		return ;// handle error
	cmd->redir->pos = START;
	_execmd(all, msh, cmd);
	cmd = cmd->next;
	while (cmd && cmd->next)
	{
		cmd->redir->pos = MID;
		_execmd(all, msh, cmd);
		cmd = cmd->next;
		// sleep(1);
	}
	if (cmd)
	{
		cmd->redir->pos = END;
		_execmd(all, msh, cmd);
	}
	close(cmd->redir->pipe_fd[1]);
	close(cmd->redir->pipe_fd[0]);
	// fprintf(stderr, "____________________________________________________\n\n");
	(void)tfd;
}

/// ON ECRIT DANS PIPE_FD[1]
/// ON LIT DANS PIPE_FD[0]

void	chromakopia(t_cmd *cmd)
{
	if (!cmd->redir)
		return ;
	else if (cmd->redir->pos == SOLO)
	{
		fprintf(stderr, "SOLO\n");
		if (cmd->redir->in_type != '0')
			if (cmd->redir->in_type == 'f')
				if(dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1)
					wgas("!chromakopia // 23\n", 22);;// handle error
		if (cmd->redir->out_type != '0')
		{
			if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
				wgas("!chromakopia // 26\n", 22);// handle error
			close(cmd->redir->pipe_fd[1]);
		}
	}
	else if (cmd->redir->pos == START)
	{
		fprintf(stderr, "START\n");
		if (dup2(cmd->redir->pipe_fd[1], STDOUT_FILENO) == -1)
			return ;// handle error
	}
	else if (cmd->redir->pos == MID)
	{
		fprintf(stderr, "MID\n");
		if (dup2(cmd->redir->pipe_fd[0], STDIN_FILENO) == -1)
			return ;// handle error
		if (dup2(cmd->redir->pipe_fd[1], STDOUT_FILENO) == -1)
			return ;// handle error
		close(cmd->redir->pipe_fd[1]);
		close(cmd->redir->pipe_fd[0]);
	}
	else if (cmd->redir->pos == END)
	{
		fprintf(stderr, "END\n");
		if (dup2(cmd->redir->pipe_fd[0], STDIN_FILENO) == -1)
			return ;// handle error
	}
	if (cmd->redir->in_type != '0')
	{
		if (cmd->redir->in_type == 'f')
			if(dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1)
				wgas("!chromakopia // 36\n", 22);;// handle error
	}
	if (cmd->redir->out_type != '0')
	{
		if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
			wgas("!chromakopia // 39\n", 22);// handle error
		
	}
	close(cmd->redir->pipe_fd[0]);
}