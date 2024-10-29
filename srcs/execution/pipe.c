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

	msh->_stdin_save = dup(STDIN_FILENO);
	tfd = 0;
	msh->pipe_fd[0] = -2;
	msh->pipe_fd[1] = -2;
	if (pipe(msh->pipe_fd) == -1)
		return ;// handle error
	fprintf(stderr, "B : %d\n", msh->pipe_fd[0]);
	fprintf(stderr, "B : %d\n", msh->pipe_fd[1]);
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
		fprintf(stderr, "MID PIPE : %d\n", msh->pipe_fd[0]);
		fprintf(stderr, "MID PIPE : %d\n", msh->pipe_fd[1]);
		cmd->redir->pos = MID;
		_execmd(all, msh, cmd);
		dup2(msh->pipe_fd[0], STDIN_FILENO);

		close(msh->pipe_fd[1]);
		close(msh->pipe_fd[0]);
		cmd = cmd->next;
		// sleep(1);
	}
	if (cmd)
	{
		cmd->redir->pos = END;
		_execmd(all, msh, cmd);
	}
	dup2(msh->_stdin_save, STDIN_FILENO);
	close(msh->_stdin_save);
	fprintf(stderr, "ICIIIIIIIIIIIIIIIIII\n");
	// close(msh->pipe_fd[1]);
	// close(msh->pipe_fd[0]);
	fprintf(stderr, "ICIIzzzzzzzzzzzzzzzzzzzzzzzzIIII\n");

	// fprintf(stderr, "____________________________________________________\n\n");
	(void)tfd;
}

/// ON ECRIT DANS PIPE_FD[1]
/// ON LIT DANS PIPE_FD[0]

void	chromakopia(t_msh *msh, t_cmd *cmd)
{
	if (!cmd->redir)
		return ;
	// fprintf(stderr, "POS : %d : PIPE VALUE %d\n", cmd->redir->pos, msh->pipe_fd[0]);
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
			close(msh->pipe_fd[1]);
		}
	}
	else if (cmd->redir->pos == START)
	{
		fprintf(stderr, "START\n");
		close(msh->_stdin_save);

		if (dup2(msh->pipe_fd[1], STDOUT_FILENO) == -1)
			wgas("!chromakopia // 26\n", 22);
	}
	else if (cmd->redir->pos == MID)
	{
		fprintf(stderr, "MID\n");
		// if (dup2(msh->pipe_fd[0], STDIN_FILENO) == -1)
		// 	return ;// handle error
		close(msh->_stdin_save);
		if (dup2(msh->pipe_fd[1], STDOUT_FILENO) == -1)
			return ;// handle error
		// close(msh->pipe_fd[1]);
		// close(msh->pipe_fd[0]);
	}
	else if (cmd->redir->pos == END)
	{
		close(msh->_stdin_save);

		fprintf(stderr, "END\n");
		// fprintf(stderr, "END : %d\n", cmd->redir.);

		// fprintf(stderr, "END : %d\n", msh->pipe_fd[0]);
		// if (dup2(msh->pipe_fd[0], STDIN_FILENO) == -1)
		// {
		// 	fprintf(stderr, "FAILED PTN\n");

		// 	return ;// handle error
		// }
		// if (dup2(STDOUT_FILENO) == -1)
		// 	return ;// handle error
	}
	if (cmd->redir && cmd->redir->in_type != '0')
	{
		if (cmd->redir->in_type == 'f')
			if(dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1)
				wgas("!chromakopia // 36\n", 22);;// handle error
	}
	if (cmd->redir && cmd->redir->out_type != '0')
	{
		if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
			wgas("!chromakopia // 39\n", 22);// handle error
	}
	// fprintf(stderr, "REAL END\n");
	close(msh->pipe_fd[0]);
	close(msh->pipe_fd[1]);
	fprintf(stderr, "POS : %d-----\n", cmd->redir->pos);
}
