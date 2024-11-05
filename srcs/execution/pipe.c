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
	if (pipe(msh->pipe_fd) == -1)
		return ;
	_execmd(all, msh, cmd, START);
	dup2(msh->pipe_fd[0], STDIN_FILENO);
	close(msh->pipe_fd[1]);
	close(msh->pipe_fd[0]);
	cmd = cmd->next;
	while (cmd && cmd->name && cmd->next)
	{
		if (pipe(msh->pipe_fd) == -1)
			return ;
		_execmd(all, msh, cmd, MID);
		dup2(msh->pipe_fd[0], STDIN_FILENO);
		close(msh->pipe_fd[1]);
		close(msh->pipe_fd[0]);
		cmd = cmd->next;
	}
	if (cmd && cmd->name)
	{
		_execmd(all, msh, cmd, END);
		close(msh->pipe_fd[1]);
		close(msh->pipe_fd[0]);
	}
}

static	void	wgas_pipe(t_all *all, t_msh *msh, char *str)
{
	free(msh->pwd);
	free(msh->data);
	freenv(msh->env);
	close(msh->pipe_fd[0]);
	close(msh->pipe_fd[1]);
	free_all_struct(all, 1);
	printf("pipe // %s\n", str);
	exit(22);
}

void	chromakopia(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	if (!cmd->redir)
		return ;
	if (pos != SOLO)
		close(msh->_stdin_save);
	if (pos == START || pos == MID)
		if (dup2(msh->pipe_fd[1], STDOUT_FILENO) == -1)
			wgas_pipe(all, msh, "!chromakopia // 66\n");
	if (cmd->redir->in_type == 'f')
		if (dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1)
			wgas_pipe(all, msh, "!chromakopia // 70\n");
	if (cmd->redir->in_type == 's' && cmd->redir->in_txt)
		if (dup2(cmd->redir->tfile, STDIN_FILENO) == -1)
			wgas_pipe(all, msh, "!chromakopia // 78\n");
	if (cmd->redir->out_type != '0')
		if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
			wgas_pipe(all, msh, "!chromakopia // 73\n");
	if (pos == SOLO)
		return ;
	close(msh->pipe_fd[0]);
	close(msh->pipe_fd[1]);
}

// cmd->redir->tfile = open(".tfile.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);
// ft_putstr_fd(cmd->redir->in_txt, cmd->redir->tfile);
// if (dup2(cmd->redir->tfile, STDIN_FILENO) == -1)
// 	wgas_pipe(all, msh, "!chromakopia // 78\n");
// close(cmd->redir->tfile);