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

static	void	set_execve(t_msh *msh, t_cmd *cmd);

int	_execmd(t_all *all, t_msh *msh, t_cmd *cmd)
{
	pid_t	tpid;
	int		i;

	// fprintf(stderr, "\n_________________________________________\n\n");
	tpid = fork();
	if (tpid == -1)
		return (1); //handle error
	if (tpid == 0) //// DANS LE PROCESS CHILD
	{
		if (is_a_buitin(msh, cmd))
			exit(0);
		else if (cmd && cmd->name)
		{
			set_execve(msh, cmd);
			if (!msh->data)
				exit(0);
			else if (execve(msh->data->path, msh->data->argv, msh->data->envp) == -1)// if cmd == '.' || '..' it will fail, so need to free everything
			{
				free(msh->data->path);
				fsplit(msh->data->argv);
				fsplit(msh->data->envp);
				exit(1);// handle error
			}	
		}
	} //// DANS LE PROCESS CHILD
	// fprintf(stderr, "111111111111111111111111111111111\n");
	waitpid(tpid, NULL, 0);
	(void)i;
	(void)all;
	return (0);
}

static	void	set_execve(t_msh *msh, t_cmd *cmd)
{
	msh->data->path = fpath(msh->env, cmd->name, -1);
	if (!msh->data->path)
	{
		fprintf(stderr, "%s: command not found\n", cmd->name);
		msh->data = NULL;
		return ;
	}
	msh->data->argv = setup_args(cmd->name, cmd->argv);
	if (!msh->data->argv)
	{
		free(msh->data->path);
		msh->data = NULL;
		return ;
	}
	msh->data->envp = setup_env(msh->env);
	if (!msh->data->envp)
	{
		free(msh->data->path);
		fsplit(msh->data->argv);
		msh->data = NULL;
	}
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
