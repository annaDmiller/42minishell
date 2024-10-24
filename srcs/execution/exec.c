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
		return (NULL); // handle error
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
		return (NULL); // handle error
	while (++i < l)
	{
		envp[i] = tjoin(tjoin(tstrdup(env->name), "="), env->var);
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	_execmd(t_msh *msh, t_cmd *cmd)
{
	char	**argv;
	char	**envp;
	char	*path;
	pid_t	tpid;

	// fprintf(stderr, "\n_________________________________________\n\n");
	tpid = 0;
	if (is_a_buitin(msh, cmd))
		return (0);
	if (!cmd->redir)
	{
		tpid = fork();
		if (tpid == -1)
			return (3);// handle error
	}
	if (cmd && cmd->name && ((!cmd->redir && tpid == 0) || (cmd->redir)))
	{
		path = fpath(msh->env, cmd->name, -1);
		if (!path)
		{
			fprintf(stderr, "%s: command not found\n", cmd->name);
			return (0);
		}
		argv = setup_args(cmd->name, cmd->argv);
		if (!argv)
			free(path);
		envp = setup_env(msh->env);
		if (!envp)
		{
			free(path);
			fsplit(argv);
		}
		if (execve(path, argv, envp) == -1)// if cmd == '.' || '..' it will fail, so need to free everything
		{
			free(path);
			fsplit(argv);
			fsplit(envp);
			exit(1);// handle error
			return (0);
		}	
	}
	if (!cmd->redir && tpid > 0)
		waitpid(tpid, NULL, 0);
	return (0);
}

char	*fpath(t_env *env, char *cmd, int i)
{
	char	**str;
	char	*path;

	if (!access(cmd, F_OK | X_OK))// try to acces the cmd right now, maybe its it absolute path
		return (cmd);
	if (!env_retrieve_var(env, "PATH") || !env_retrieve_var(env, "PATH")->var)
		return (NULL);
	path = NULL;
	str = split(env_retrieve_var(env, "PATH")->var, ':');
	if (!str)
		return (NULL);
	while (str[++i])
	{
		str[i] = tjoin(tjoin(str[i], "/"), cmd);// building paths
		if (!access(str[i], F_OK | X_OK))// check if the file of the path exist and if its executable
			break ;// if yes we break the loop
	}
	if (str[i])// if we didnt find any path str[i] == NULL it wont check the condition
		path = tstrdup(str[i]);
	fsplit(str);
	return (path);
}
