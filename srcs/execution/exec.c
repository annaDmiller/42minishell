/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:23:32 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/23 05:02:01 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	void	_exec_child(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos);
static	int	fds(t_cmd *cmd);
static	int	exec_fail(t_all *all, t_msh *msh, t_cmd *cmd);
static	void	check_signal_exit(t_all *all, int rtval);

int	_execmd(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	struct sigaction	*old;
	pid_t				tpid;
	int					rtval;

	rtval = 0;
	if (!cmd || ((pos == SOLO && !cmd->redir && (cmd->name
					&& tstrcmp(cmd->name, "env") && exec_buitin(msh, cmd)))))
		return (0);
	tpid = fork();
	if (tpid == -1)
		return (1);
	if (tpid == 0)
		_exec_child(all, msh, cmd, pos);
	if (pos == SOLO || pos == END)
	{
		old = sigint_ign_wait(all, 1);
		waitpid(tpid, &rtval, 0);
		restore_sigint_hdl(all, old);
		if (WIFEXITED(rtval))
			msh->exit = WEXITSTATUS(rtval);
		check_signal_exit(all, rtval);
	}
	return (0);
}

static	void	_exec_child(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	init_signals_child();
	chromakopia(all, msh, cmd, pos);
	if (!cmd->name || g_sig || !cmd->has_to_be_executed)
	{
		free_exit(all, msh, 1);
		exit(0);
	}
	if (exec_buitin(msh, cmd))
	{
		free_exit(all, msh, 1);
		exit(msh->exit);
	}
	else if (cmd && cmd->name)
	{
		if (!cmd_check(all, msh, cmd) || (!tstrcmp(cmd->name, ""))
			|| !set_execve(msh, cmd))
		{
			err_msg(NULL, cmd->name, "command not found\n");
			free_exit(all, msh, 1);
			exit(127);
		}
		fds(cmd);
		if (execve(msh->data->path, msh->data->argv, msh->data->envp) == -1)
			exec_fail(all, msh, cmd);
	}
}

static	int	fds(t_cmd *cmd)
{
	if (cmd->redir && cmd->redir->fd_infile)
		close(cmd->redir->fd_infile);
	if (cmd->redir && cmd->redir->fd_outfile)
		close(cmd->redir->fd_outfile);
	return (1);
}

static	int	exec_fail(t_all *all, t_msh *msh, t_cmd *cmd)
{
	err_msg(NULL, cmd->name, "execution failed\n");
	free(msh->data->path);
	fsplit(msh->data->argv);
	fsplit(msh->data->envp);
	free_exit(all, msh, 1);
	exit(1);
}

static	void	check_signal_exit(t_all *all, int rtval)
{
	if (WIFSIGNALED(rtval) && (WTERMSIG(rtval) == SIGINT
			|| WTERMSIG(rtval) == SIGQUIT))
	{
		if (WTERMSIG(rtval) == SIGINT)
			all->msh->exit = 130;
		if (WTERMSIG(rtval) == SIGQUIT)
		{
			putstderr("Quit (core dumped)");
			all->msh->exit = 131;
		}
		printf("\n");
	}
}
