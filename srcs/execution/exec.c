/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:23:32 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/06 22:12:29 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	void	_exec_child(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos);

int	_execmd(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	struct sigaction	*old;
	pid_t				tpid;
	int					rtval;

	rtval = 0;
	if (!cmd || (!cmd->has_to_be_executed))
		return (0);
	if (pos == SOLO && !cmd->redir && (cmd->name && exec_buitin(msh, cmd)))
		return (0);
	tpid = fork();
	if (tpid == -1)
		return (1);
	if (tpid == 0)
		_exec_child(all, msh, cmd, pos);
	if (pos == SOLO || pos == END)
	{
		rtval = 0;
		old = sigint_ign_wait(all, 1);
		waitpid(tpid, &rtval, 0);
		restore_sigint_hdl(all, old);
		if (WIFEXITED(rtval))
			msh->exit = WEXITSTATUS(rtval);
		if (WIFSIGNALED(rtval) && WTERMSIG(rtval) == SIGINT)
			printf("\n");
	}
	return (0);
}

static	void	_exec_child(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	signal(SIGINT, SIG_DFL);
	chromakopia(all, msh, cmd, pos);
	if (!cmd->name || g_sig)
	{
		free_exit(all, msh, 1);
		exit(0);
	}
	if (is_a_buitin(cmd->name))
	{
		exec_buitin(msh, cmd);
		free_exit(all, msh, 1);
		exit(msh->exit);
	}
	else if (cmd && cmd->name)
	{
		if (!cmd_check(all, msh, cmd) || (!tstrcmp(cmd->name, "")) || !set_execve(msh, cmd))
		{
			ft_putstr_fd(cmd->name, 2);
			ft_putstr_fd(": command not found\n", 2);
			free_exit(all, msh, 1);
			exit(127);
		}
		if (execve(msh->data->path, msh->data->argv, msh->data->envp) == -1)
		{
			printf("%s: execution failed\n", cmd->name);
			free(msh->data->path);
			fsplit(msh->data->argv);
			fsplit(msh->data->envp);
			free_exit(all, msh, 1);
			exit(1);
		}
	}
}

int	cmd_check(t_all *all, t_msh *msh, t_cmd *cmd)
{
	DIR	*dir;

	if (!cmd || (cmd && !cmd->name) || (!cmd->has_to_be_executed))
		return (0);
	dir = opendir(cmd->name);
	if (dir)
	{
		closedir(dir);
		ft_putstr_fd(cmd->name, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		free_exit(all, msh, 1);
		exit(126);
		return (0);
	}
	return (1);
}
