/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 23:31:46 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 14:04:09 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

int	is_a_buitin(t_msh *msh, t_cmd *cmd)
{
	if (tstrcmp(cmd->name,"env"))
		env(msh->env);
	if (tstrcmp(cmd->name,"pwd"))
		printf("%s\n", msh->pwd);
	if (tstrcmp(cmd->name,"echo"))
		echo(msh, cmd);
	if (tstrcmp(cmd->name,"cd"))
		cd(msh, cmd->argv);
	if (tstrcmp(cmd->name,"export"))
		export(msh, cmd->argv);
	if (tstrcmp(cmd->name,"unset"))
		unset(msh, cmd->argv);
	if (tstrcmp(cmd->name,"exit"))
		texit(msh, cmd->argv);
	return (0);
}

/// @brief Display the environnement		variable=value
/// // //   if there is no value, it just print variable=""
/// @param t_env *env 
void    env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	printf("\n");
	while (tmp)
	{
		/// si la variable n'a pas de valeur on affiche des double quotes sans rien
		printf("%s=", tmp->name);
		if (tmp->var)
			printf("%s\n", tmp->var);
		else
			printf("""\n");
		// printf("%d\t%s\n", tmp->id, tmp->name);
		// printf("%s // %s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
	printf("\n");
}
/// @brief if path given argv->arg is not valid it prints pathname: No such file or directory
///	if there is more than one arg it doesnt move and prints cd: too many arguments
void    cd(t_msh *msh, t_args *argv)
{
	// char	*tmp;
	DIR	*test;
	char	*path;

	// tmp = msh->pwd;
	if (argv->next)
		return (putstrfd("cd: too many arguments\n", STDOUT_FILENO));
	path = argv->arg;
	(void)msh;
	test = opendir(path);
	if (test)
		if (!chdir(".."))
			return ; // handle error

	//if cmd is ../../sgoinfr --> make the right pwd be
	// if (path[0] == '.' && path[1] == '.')
		// down_pwd(msh);
		// msh->pwd = handle going backward, crop everything after the last '/'
	// else if (path == ".")
		// "." mean current directory so no need to handle this ?
}

void    up_pwd(t_msh *msh, char *dir)
{
	char	*nvx_pwd;

	nvx_pwd = tjoin(tjoin(tstrdup(msh->pwd), "/"), dir);
	free(msh->pwd);
	msh->pwd = nvx_pwd;
	// env->OLD_PWD = tmp; // set OLD_PWD to the current pwd if chdir succeed
}

void    down_pwd(t_msh *msh)
{
	char	*nvx_pwd;
	// char	*tmp;
	int	i;
	int	d;

	// tmp = msh->pwd;
	i = tstrlen(msh->pwd);
	while (msh->pwd[--i])
		if (msh->pwd[i] == '/')
			break ;
	nvx_pwd = malloc(sizeof(char) * i + 1);
	if (!nvx_pwd)
		return ; // handle error
	d = -1;
	while (++d < i)
		nvx_pwd[d] = msh->pwd[d];
	nvx_pwd[d] = '\0';
	free(msh->pwd);
	msh->pwd = nvx_pwd;
	// env->OLD_PWD = tmp; // set OLD_PWD to the current pwd if chdir succeed
}

// echo -nnnnnnnnnnn talan
// should work
// echo -nd talan
// should printf -nd talan

