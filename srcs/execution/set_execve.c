/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_execve.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:12:08 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/06 22:12:09 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

//// how to handle '.' or '..'
int	set_execve(t_msh *msh, t_cmd *cmd)
{
	msh->data->path = fpath(msh->env, cmd->name, -1);
	if (!msh->data->path)
	{
		printf("%s: command not found\n", cmd->name);
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

	// msh->data->argv = malloc(sizeof(char *) * 2);
	// if (!msh->data->argv)
	// {
	// 	free(msh->data->path);
	// 	return (0);
	// }
	// msh->data->argv[0] = tstrdup(".eof");
	// msh->data->argv[1] = NULL;

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
	str = ft_split(env_retrieve_var(env, "PATH")->var, ':');
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
