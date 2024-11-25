/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:33:18 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/06 22:13:08 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	tpipe(t_all *all, t_msh *msh, t_cmd *cmd)
{
	if (pipe(msh->pipe_fd) == -1)
		return ;
	_execmd(all, msh, cmd, START);
	dup2(msh->pipe_fd[0], STDIN_FILENO);
	close(msh->pipe_fd[1]);
	close(msh->pipe_fd[0]);
	cmd = cmd->next;
	while (cmd && cmd->next)
	{
		if (pipe(msh->pipe_fd) == -1)
			return ;
		_execmd(all, msh, cmd, MID);
		dup2(msh->pipe_fd[0], STDIN_FILENO);
		close(msh->pipe_fd[1]);
		close(msh->pipe_fd[0]);
		cmd = cmd->next;
	}
	if (cmd)
	{
		_execmd(all, msh, cmd, END);
		close(msh->pipe_fd[1]);
		close(msh->pipe_fd[0]);
	}
}

static	void	wgas_pipe(t_all *all, t_msh *msh, t_pos pos)
{
	free(msh->pwd);
	if (msh->home)
		free(msh->home);
	free(msh->data);
	freenv(msh->env);
	if (pos != SOLO)
	{
		close(msh->pipe_fd[0]);
		close(msh->pipe_fd[1]);
	}
	free_all_struct(all, 1);
	exit(22);
}

static int	fds_opening(t_cmd *cmd, t_fds *fds)
{
	if (cmd->redir->in_type != '0')
	{
		if (cmd->redir->in_type == 'f')
			fds->fd_infile = open(cmd->redir->infile, O_RDONLY);
		if (fds->fd_infile == -1)
			return (cmd->has_to_be_executed = 0, err_msg(NULL,
					cmd->redir->infile, "No such file or directory\n"), 0);
	}
	if (cmd->redir->out_type != '0')
	{
		if (cmd->redir->out_type == 'r')
			fds->fd_outfile = open(cmd->redir->outfile,
					O_WRONLY | O_TRUNC | O_CREAT, 0666);
		else if (cmd->redir->out_type == 'a')
			fds->fd_outfile = open(cmd->redir->outfile,
					O_WRONLY | O_APPEND | O_CREAT, 0666);
		if (fds->fd_outfile == -1)
			return (cmd->has_to_be_executed = 0, err_msg(NULL,
					cmd->redir->outfile, "couldnt retrieve/create\n"), 0);
	}
	return (1);
}

void	chromakopia(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	if (!cmd->redir || !fds_opening(cmd, cmd->fds))
		return ;
	if (g_sig)
		return (free_exit(all, msh, 1), exit(SIGINT));
	if (pos != SOLO)
		close(msh->_stdin_save);
	if (pos == START || pos == MID)
		if (dup2(msh->pipe_fd[1], STDOUT_FILENO) == -1)
			wgas_pipe(all, msh, pos);
	if (cmd->redir->in_type != '0')
	{
		if (cmd->redir->in_type == 's')
			cmd->fds->fd_infile = open(".eof", O_RDONLY, 0644);
		if (dup2(cmd->fds->fd_infile, STDIN_FILENO) == -1)
			wgas_pipe(all, msh, pos);
	}
	if (cmd->redir->out_type != '0')
		if (dup2(cmd->fds->fd_outfile, STDOUT_FILENO) == -1)
			wgas_pipe(all, msh, pos);
	if (pos == SOLO)
		return ;
	close(msh->pipe_fd[0]);
	close(msh->pipe_fd[1]);
}
