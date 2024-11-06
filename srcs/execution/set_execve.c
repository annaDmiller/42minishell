#include "../../includes/minishell.h"
//// how to handle '.' or '..'

/// @brief set everything execve(char *path, char **argv, char **envp) in a msh->data struct
/// @return 0 if it failed, 1 if everything is ok
int	set_execve(t_msh *msh, t_cmd *cmd)
{
	msh->data->path = fpath(msh->env, cmd->name, -1);
	if (!msh->data->path)
	{
		printf("%s: command not found\n", cmd->name);
		return (0);
	}
	msh->data->argv = setup_argv(cmd->name, cmd->argv);
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


/// @brief building a char **argv as it is in bash and needed for execve
char	**setup_arg(char *name, t_args *argv)
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

/// @brief building a char **envp as it is in bash and needed for execve
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

	if (!access(cmd, F_OK | X_OK)) // check if the cmd->name isnt already the absolut path of the cmd
		return (cmd);
	if (!env_retrieve_var(env, "PATH") || !env_retrieve_var(env, "PATH")->var) // check if the path env variable exists
		return (NULL);
	path = NULL;
	str = ft_split(env_retrieve_var(env, "PATH")->var, ':'); // split the PATH content with ':'
	if (!str)
		return (NULL);
	while (str[++i])
	{
		str[i] = tjoin(tjoin(str[i], "/"), cmd); // tjoin str[i] with '/cmd' to try to access it with the proper path
		if (!access(str[i], F_OK | X_OK)) // if access succeed, we found the path of the cmd and break from that loop
			break ;
	}
	if (str[i]) // if str[i] it means we break out of the loop after succeeding to access str[i] path
		path = tstrdup(str[i]); // keep a copy of it so we can free the split we did later
	fsplit(str);
	return (path); // return the path, if we didnt access anything path will stay as it is : NULL
}
