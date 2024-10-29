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
	msh->_stdin_save = dup(STDIN_FILENO);
	msh->pipe_fd[0] = -2;
	msh->pipe_fd[1] = -2;
	if (pipe(msh->pipe_fd) == -1)
		return ;// handle error
	cmd->redir->pos = START;
	_execmd(all, msh, cmd);
	dup2(msh->pipe_fd[0], STDIN_FILENO);
	close(msh->pipe_fd[1]);
	close(msh->pipe_fd[0]);
	cmd = cmd->next;
	while (cmd && cmd->next)
	{
		if (pipe(msh->pipe_fd) == -1)
			return ;// handle error
		cmd->redir->pos = MID;
		_execmd(all, msh, cmd);
		dup2(msh->pipe_fd[0], STDIN_FILENO);
		close(msh->pipe_fd[1]);
		close(msh->pipe_fd[0]);
		cmd = cmd->next;
	}
	if (cmd)
	{
		cmd->redir->pos = END;
		_execmd(all, msh, cmd);
	}
	dup2(msh->_stdin_save, STDIN_FILENO);
	close(msh->_stdin_save);
	// fprintf(stderr, "____________________________________________________\n\n");
}

/// ON ECRIT DANS PIPE_FD[1]
/// ON LIT DANS PIPE_FD[0]

void	chromakopia(t_msh *msh, t_cmd *cmd)
{
	if (!cmd->redir)
		return ;
	else if (cmd->redir->pos == START)
	{
		close(msh->_stdin_save);
		fprintf(stderr, "%d\n", cmd->redir->pipe_fd[0]);
		fprintf(stderr, "%d\n", cmd->redir->pipe_fd[1]);
		if (dup2(msh->pipe_fd[1], STDOUT_FILENO) == -1)
			wgas("!chromakopia // 90\n", 22);
		fprintf(stderr, "JDOQIOJIWDIDJQWIOJQDWQDOIWJQWDOJIWDQIOJ\n");
	}
	else if (cmd->redir->pos == MID)
	{
		close(msh->_stdin_save);
		if (dup2(msh->pipe_fd[1], STDOUT_FILENO) == -1)
			wgas("!chromakopia // 97\n", 22);
	}
	else if (cmd->redir->pos == END)
		close(msh->_stdin_save);
	if (cmd->redir && cmd->redir->in_type != '0')
		if (cmd->redir->in_type == 'f')
			if (dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1)
				wgas("!chromakopia // 108\n", 22);// handle error
	if (cmd->redir && cmd->redir->out_type != '0')
		if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
			wgas("!chromakopia // 113\n", 22);// handle error
	if (cmd->redir && cmd->redir->pos == SOLO)
		return ;
	close(msh->pipe_fd[0]);
	close(msh->pipe_fd[1]);
	// fprintf(stderr, "JDOQIOJIWDIDJQWIOJQDWQDOIWJQWDOJIWDQIOJ\n");
	fprintf(stderr, "%d\n", STDOUT_FILENO);
}
