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

static	int	set_execve(t_msh *msh, t_cmd *cmd);

static	void	msh_free(t_msh *msh);

int	_execmd(t_all *all, t_msh *msh, t_cmd *cmd, t_pos pos)
{
	pid_t	tpid;
	int		rtval;

	if (((!tstrcmp(cmd->name, "unset")) || (!tstrcmp(cmd->name, "cd"))
		|| ((!tstrcmp(cmd->name, "export") && cmd->argv)) || (!tstrcmp(cmd->name, "exit"))))
		if (!cmd->redir || cmd->redir->pos == SOLO)
			return (is_a_buitin(msh, cmd));
	tpid = fork();
	if (tpid == -1)
		return (1);
	if (tpid == 0)
	{
		chromakopia(all, msh, cmd, pos);
		if (is_a_buitin(msh, cmd))
		{
			msh_free(msh);
			if (msh->_stdin_save > 0)
				close(msh->_stdin_save);
			free_all_struct(all, 1);
			exit(0);
		}
		else if (cmd && cmd->name)
		{
			if (!set_execve(msh, cmd))
			{
				msh_free(msh);
				free_all_struct(all, 1);
				exit(35);
			}
			if (execve(msh->data->path, msh->data->argv, msh->data->envp) == -1)
			{
				free(msh->data->path);
				fsplit(msh->data->argv);
				fsplit(msh->data->envp);
				msh_free(msh);
				free_all_struct(all, 1);
				wgas("!_execve // 43", 43);
				exit(1);
			}
		}
	}
	waitpid(tpid, &rtval, 0);
		if (WIFEXITED(rtval))
			msh->exit = WEXITSTATUS(rtval);
	return (0);
}

static	void	msh_free(t_msh *msh)
{
	free(msh->pwd);
	free(msh->data);
	freenv(msh->env);
}

static	int	set_execve(t_msh *msh, t_cmd *cmd)
{
	msh->data->path = fpath(msh->env, cmd->name, -1);
	if (!msh->data->path)
	{
		printf("cmd->name : [%s]\t\t%s: command not found\n", cmd->name, cmd->name);
		return (0);
	}
	msh->data->argv = setup_args(cmd->name, cmd->argv);
	if (!msh->data->argv)
	{
		free(msh->data->path);
		return (0);
	}
	msh->data->envp = setup_env(msh->env);
	if (!msh->data->envp)
	{
		free(msh->data->path);
		fsplit(msh->data->argv);
		return (0);
	}
	return (1);
}

char	**setup_args(char *name, t_args *argv)
{
	t_args	*tmp;
	char	**args;
	int		i;
	int		l;

	i = 0;
	tmp = argv;
	l = l_argsize(argv) + 1;
	args = (char **)malloc(sizeof(char *) * (l + 1));
	if (!args)
		return (NULL);
	args[0] = tstrdup(name);
	while (++i < l)
	{
		args[i] = tstrdup(argv->arg);
		argv = argv->next;
	}
	args[i] = NULL;
	(void)tmp;
	return (args);
}

char	**setup_env(t_env *env)
{
	char	**envp;
	int		i;
	int		l;

	i = -1;
	l = l_envsize(env);
	envp = (char **)malloc(sizeof(char *) * (l + 1));
	if (!envp)
		return (NULL);
	while (++i < l)
	{
		envp[i] = tjoin(tjoin(tstrdup(env->name), "="), env->var);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

char	*fpath(t_env *env, char *cmd, int i)
{
	char	**str;
	char	*path;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	if (!env_retrieve_var(env, "PATH") || !env_retrieve_var(env, "PATH")->var)
		return (NULL);
	path = NULL;
	str = split(env_retrieve_var(env, "PATH")->var, ':');
	if (!str)
		return (NULL);
	while (str[++i])
	{
		str[i] = tjoin(tjoin(str[i], "/"), cmd);
		if (!access(str[i], F_OK | X_OK))
			break ;
	}
	if (str[i])
		path = tstrdup(str[i]);
	fsplit(str);
	return (path);
}
