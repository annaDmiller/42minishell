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

int	exec(t_msh *msh, t_cmd *cmd)
{
	char	**argv;
	char	**envp;
	char	*path;
	DIR	*test;
	pid_t	pid;
 	int		i;

	i = -1;
	// printf("\n_________________________________________\n\n");
	while (cmd && cmd->name)
	{
		if (is_a_buitin(msh, cmd))
			cmd = cmd->next;
		else if (!tstrcmp(cmd->name, ".") || !tstrcmp(cmd->name, ".."))
			cmd = cmd->next;
		else if (cmd && cmd->name)
		{
			path = fpath_tt(msh->env, cmd->name, -1);
			if (!path)
			{
				// printf("JE N'AI PAS TROUVE DE PATHHHHHH\n");
				printf("%s: command not found\n", cmd->name);
				break ;
			}
			argv = setup_args(cmd->name, cmd->argv);
			if (!argv)
			{
				free(path);
				break ;
			}
			envp = setup_env(msh->env);
			if (!envp)
			{
				free(path);
				fsplit(argv);
				break ;
			}
			pid = fork();
			// if (pid == -1)
				// return (NULL) handle error
			if (pid == 0)
				cute(path, argv, envp);
			// if (cute(path, argv, envp) == -1)
			// 	return (0); // handle error
			waitpid(pid, NULL, 0);
			free(path);
			fsplit(argv);
			fsplit(envp);
			cmd = cmd->next;
		}
	}
	(void)i;
	(void)argv;
	(void)path;
	(void)test;
	(void)msh;
	return (0);
}

int	cute(char *path, char **argv, char **envp)
{
	int	pid;
	int		i;

	i = 0;
	pid = fork();
	if (pid == 0)
		if (execve(path, argv, envp) == -1)
			return (-1);
	if (pid)
		i++;
	(void)i;
	return (0);
}

char	*fpath_tt(t_env *env, char *cmd, int i)
{
	char	**str;
	char	*path;

	if (!env_retrieve_var(env, "PATH") || !env_retrieve_var(env, "PATH")->var)
		return (NULL);
	if (!access(cmd, F_OK | X_OK))// try to acces the cmd right now, maybe its it absolute path
		return (cmd);
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
