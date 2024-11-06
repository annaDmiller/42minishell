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

static	void	wgas_pipe(t_all *all, t_msh *msh, char *str)

void	tpipe(t_all *all, t_msh *msh, t_cmd *cmd)
{
	if (pipe(msh->pipe_fd) == -1) // pipe the shared msh->pipe_fd
		return ;
	_execmd(all, msh, cmd, START); // exec the first cmd START
	dup2(msh->pipe_fd[0], STDIN_FILENO);
	close(msh->pipe_fd[1]); // leaks purpose
	close(msh->pipe_fd[0]); // leaks purpose
	cmd = cmd->next;
	while (cmd && cmd->name && cmd->next) // while we arent to the last cmd 
	{
		if (pipe(msh->pipe_fd) == -1) // pipe the shared msh->pipe_fd
			return ;
		_execmd(all, msh, cmd, MIDDLE); // exec the cmd in between MIDLE
		dup2(msh->pipe_fd[0], STDIN_FILENO);
		close(msh->pipe_fd[1]); // leaks purpose
		close(msh->pipe_fd[0]); // leaks purpose
		cmd = cmd->next;
	}
	if (cmd && cmd->name)
	{
		_execmd(all, msh, cmd, END); // exec the last cmd END
		close(msh->pipe_fd[1]); // leaks purpose
		close(msh->pipe_fd[0]); // leaks purpose
	}
}

void	chromakopia(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	if (!cmd->redir)
		return ;
	if (pos != SOLO)
		close(msh->_stdin_save); // close stdin only if there is a pipe
	if (pos == START || pos == MIDDLE) // if its not the last cmd
		if (dup2(msh->pipe_fd[1], STDOUT_FILENO) == -1) // redirect the STDOUT --> pipe
			wgas_pipe(all, msh, "!chromakopia // 66\n");
	if (cmd->redir->in_type == 'f') // if theres an infile redirection
		if (dup2(cmd->redir->fd_infile, STDIN_FILENO) == -1) // redirect the STDIN --> infile
			wgas_pipe(all, msh, "!chromakopia // 70\n");
	if (cmd->redir->in_type == 's' && cmd->redir->in_txt) // if its a heredoc
		if (dup2(cmd->redir->tfile, STDIN_FILENO) == -1) // redirect the STDIN --> .tfile.txt
			wgas_pipe(all, msh, "!chromakopia // 78\n");
	if (cmd->redir->out_type != '0') // if theres an outfile redirection
		if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1) // redirect the STDOUT --> outfile
			wgas_pipe(all, msh, "!chromakopia // 73\n");
	if (pos == SOLO)
		return ;
	close(msh->pipe_fd[0]); // close pipe fds inside child process
	close(msh->pipe_fd[1]); // close pipe fds inside child process
}

/// @brief if an error occurs inside chromakopia
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

// cmd->redir->tfile = open(".tfile.txt", O_WRONLY | O_TRUNC | O_CREAT, 0666);
// ft_putstr_fd(cmd->redir->in_txt, cmd->redir->tfile);
// if (dup2(cmd->redir->tfile, STDIN_FILENO) == -1)
// 	wgas_pipe(all, msh, "!chromakopia // 78\n");
// close(cmd->redir->tfile);