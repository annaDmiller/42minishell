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
		fprintf(stderr, "MID\n");
		cmd = cmd->next;
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

	msh->_stdin_save = dup(STDIN_FILENO);
	msh->_stdout_save = dup(STDOUT_FILENO);
	if (dup2(msh->_stdin_save, STDIN_FILENO) == -1)
		return ;//handle error
	if (dup2(msh->_stdout_save, STDOUT_FILENO) == -1)
		return ;//handle error
	if (cmd->redir->in_type == 'f')
	{
		if (dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1)
			return ;// handle error
		close(cmd->redir->fd_infile);
	}
	// printf("fd[0] = %d\tfd[1] = %d\n", cmd->redir->pipe_fd[0], cmd->redir->pipe_fd[1]);
	if (dup2(cmd->redir->pipe_fd[1], STDOUT_FILENO) == -1)
		return ;//handle error
	close(cmd->redir->pipe_fd[0]);
	tpid = fork();
	if (tpid == -1)
		return ;// handle error
	if (tpid == 0)
		_execmd(msh, cmd);
	close(cmd->redir->pipe_fd[1]);
	waitpid(tpid, NULL, 0);
}

void	mid(t_msh *msh, t_cmd *cmd)
{
	pid_t	tpid;

	if (dup2(cmd->redir->pipe_fd[0], STDIN_FILENO) == -1)
		return ;// handle error
	close(cmd->redir->pipe_fd[0]);
	if (dup2(cmd->redir->pipe_fd[1], STDOUT_FILENO) == -1)
		return ;// handle error
	close(cmd->redir->pipe_fd[1]);
	tpid = fork();
	if (tpid == -1)
		return ;// handle error
	if (tpid == 0)
		_execmd(msh, cmd);
	waitpid(tpid, NULL, 0);
}

void	end(t_msh *msh, t_cmd *cmd)
{
	pid_t	tpid;

	// pas de redirection out donc l'output de la derniere commande est affiche sur le terminal (STDOOUT_FILENO)

	// fprintf(stderr, "FD // %d\n", cmd->redir->fd_outfile);
	if (cmd && cmd->redir && cmd->redir->out_type && cmd->redir->out_type == '0')
	{
		if (dup2(cmd->redir->pipe_fd[1], STDOUT_FILENO) == -1)
			return ;// handle
	}
	else if (cmd->redir->out_type != '0' && cmd->redir->fd_outfile)
		if (dup2(cmd->redir->pipe_fd[1], cmd->redir->fd_outfile) == -1)
			return ;// handle
	// if (cmd->redir->out_type != '0' && cmd->redir->fd_outfile)
		// close(cmd->redir->pipe_fd[0]);
	close(cmd->redir->pipe_fd[1]);
	close(cmd->redir->pipe_fd[0]);
	tpid = fork();
	if (tpid == -1)
		return ;// handle error
	if (tpid == 0)
		_execmd(msh, cmd);
	waitpid(tpid, NULL, 0);
	if (dup2(msh->_stdin_save, STDIN_FILENO) == -1)
		return ;//handle error
	if (dup2(msh->_stdout_save, STDOUT_FILENO) == -1)
		return ;//handle error
	close(msh->_stdin_save);
	close(msh->_stdout_save);

}
