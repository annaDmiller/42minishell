/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:23:32 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/18 20:24:12 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	void	_exec_child(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos);

int	_execmd(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	pid_t				tpid;
	int					rtval;
	struct sigaction	*old;

	if (((!tstrcmp(cmd->name, "unset")) || (!tstrcmp(cmd->name, "cd")) // if its only one cmd and its one of this four builtin
			|| ((!tstrcmp(cmd->name, "export") && cmd->argv)) // it has to be executed in the parent process otherwise
			|| (!tstrcmp(cmd->name, "exit")))) // the change wont be effective outside the child process
		if (!cmd->redir || cmd->redir->pos == SOLO)
			return (is_a_buitin(msh, cmd));
	tpid = fork(); // entering child process
	if (tpid == -1)
		return (1);
	if (tpid == 0)
		_exec_child(all, msh, cmd, pos); // exiting child process at the end
	if (pos == SOLO || pos == END) // check if its the only cmd or if its the last one of the cmd line to recover the exit code
	{
		old = sigint_ign_wait(all);
		waitpid(tpid, &rtval, 0); // wait for the child process to finish
		restore_sigint_hdl(all, old);
		if (WIFEXITED(rtval))
			msh->exit = WEXITSTATUS(rtval); // assigning msh->exit with the last executed cmd exit code
	}
	return (0);
}
/// @brief execution inside child process
static	void	_exec_child(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	signal (SIGINT, SIG_DFL);
	chromakopia(all, msh, cmd, pos); // handle every redirection 
	if (is_a_buitin(msh, cmd))
	{
		free_exit(all, msh, 0);
		exit(0);
		// exit(msh->exit);
		// hypotetically msh->exit will be reset after what happens in the builtin, then we have to exit with the exit code set
		// cause we are in child process and WEXITSTATUS(rtval) has to get the good value
	}
	else if (cmd && cmd->name)
	{
		if (!set_execve(msh, cmd))
		{
			free_exit(all, msh, 0);
			exit(127); // exit code for cmd not found but has to be something else if a malloc failed
		}
		if (execve(msh->data->path, msh->data->argv, msh->data->envp) == -1)
		{
			free(msh->data->path);
			fsplit(msh->data->argv);
			fsplit(msh->data->envp);
			free_exit(all, msh, 0);
			printf("execution failed\n");
			exit(243);
		}
	}
}
