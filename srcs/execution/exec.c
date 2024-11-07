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

	if (!cmd || (cmd && !cmd->name) || (!cmd->has_to_be_executed))
		return (0);
	if (((!tstrcmp(cmd->name, "unset")) || (!tstrcmp(cmd->name, "cd"))
			|| ((!tstrcmp(cmd->name, "export") && cmd->argv))
			|| (!tstrcmp(cmd->name, "exit"))))
		if (!cmd->redir || cmd->redir->pos == SOLO)
			return (is_a_buitin(msh, cmd));
	tpid = fork();
	if (tpid == -1)
		return (1);
	if (tpid == 0)
		_exec_child(all, msh, cmd, pos);
	if (pos == SOLO || pos == END)
	{
		old = sigint_ign_wait(all);
		waitpid(tpid, &rtval, 0);
		restore_sigint_hdl(all, old);
		if (WIFEXITED(rtval))
			msh->exit = WEXITSTATUS(rtval);
	}
	return (0);
}

static	void	_exec_child(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	signal (SIGINT, SIG_DFL);
	chromakopia(all, msh, cmd, pos);
	if (is_a_buitin(msh, cmd))
	{
		free_exit(all, msh, 1);
		exit(msh->exit);
	}
	else if (cmd && cmd->name)
	{
		if (!set_execve(msh, cmd))
		{
			free_exit(all, msh, 1);
			exit(msh->exit);
		}
		if (execve(msh->data->path, msh->data->argv, msh->data->envp) == -1)
		{
			printf("%s: Is a directory\n", cmd->name);
			free(msh->data->path);
			fsplit(msh->data->argv);
			fsplit(msh->data->envp);
			free_exit(all, msh, 1);
			exit(EXIT_FAILURE);
		}
	}
}

int	cmd_check(t_msh *msh, t_cmd *cmd)
{
	DIR	*dir;

	if (!cmd || (cmd && !cmd->name) || (!cmd->has_to_be_executed))
		return (0);
	dir = opendir(cmd->name);
	if (dir)
	{
		printf("%s: Is a directory\n", cmd->name);
		closedir(dir);
		msh->exit = 126;
		return (0);
	}
	return (1);
}
