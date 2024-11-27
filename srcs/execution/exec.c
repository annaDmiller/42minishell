/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:23:32 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/25 00:00:52 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	void	_exec_child(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos);
static	int	exec_fail(t_all *all, t_msh *msh, t_cmd *cmd);
static	void	check_signal_exit(t_all *all, int rtval);

int	_execmd(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	struct sigaction	*old;
	pid_t				tpid;
	int					rtval;

	rtval = 0;
	if (!cmd || !cmd->has_to_be_executed || ((pos == SOLO && !cmd->redir
				&& (cmd->name && tstrcmp(cmd->name, "env")
					&& exec_buitin(msh, cmd)))))
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
	if (!cmd->name || g_sig)
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
		if (!cmd_check(all, msh, cmd) || !set_execve(msh, cmd))
		{
			if (msh->exit == 126)
				err_msg(cmd->name, "Permission denied", NULL);
			free_exit(all, msh, 1);
			exit(msh->exit);
		}
		fds(all);
		printf("%s\n", msh->data->path);
		printf("%s\n", msh->data->argv[0]);
		printf("%s\n", msh->data->envp[0]);
		if (execve(msh->data->path, msh->data->argv, msh->data->envp) == -1)
			exec_fail(all, msh, cmd);
	}
}

int	fds(t_all *all)
{
	t_cmd	*cmd;

	cmd = all->lst_cmd;
	while (cmd)
	{
		if (cmd->fds && cmd->fds->fd_infile > 0)
			close(cmd->fds->fd_infile);
		if (cmd->fds && cmd->fds->fd_outfile > 0)
			close(cmd->fds->fd_outfile);
		cmd = cmd->next;
	}
	if (all->msh->_stdin_save > 0)
		close(all->msh->_stdin_save);
	return (1);
}

static	int	exec_fail(t_all *all, t_msh *msh, t_cmd *cmd)
{
	msh->exit = 0;
	if (is_a_dir(cmd->name))
	{
		err_msg(cmd->name, "Is a directory", NULL);
		msh->exit = 126;
	}
	free(msh->data->path);
	fsplit(msh->data->argv);
	fsplit(msh->data->envp);
	free_exit(all, msh, 1);
	exit(msh->exit);
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
