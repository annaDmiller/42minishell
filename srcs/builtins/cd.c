/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:16 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:18 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	cd(t_msh *msh, t_args *argv)
{
	if (!argv && !env_retrieve_var(msh->env, "HOME"))
		printf("cd: HOME not set\n");
	else if (!argv && chdir(env_retrieve_var(msh->env, "HOME")->var) == 0)
	{
		if (env_retrieve_var(msh->env, "OLDPWD"))
		{
			free(env_retrieve_var(msh->env, "OLDPWD")->var);
			env_retrieve_var(msh->env, "OLDPWD")->var = tstrdup(msh->pwd);
		}
		if (msh->pwd)
		{
			free(msh->pwd);
			msh->pwd = NULL;
		}
		msh->pwd = getcwd(NULL, 0);
	}
	else if (argv->next)
		printf("cd: too many arguments\n");
	else if (chdir(argv->arg) == 0)
	{
		if (env_retrieve_var(msh->env, "OLDPWD"))
		{
			free(env_retrieve_var(msh->env, "OLDPWD")->var);
			env_retrieve_var(msh->env, "OLDPWD")->var = tstrdup(msh->pwd);
		}
		if (msh->pwd)
		{
			free(msh->pwd);
			msh->pwd = NULL;
		}
		msh->pwd = getcwd(NULL, 0);
	}
	else
		printf("cd: %s: No such file or directory\n", argv->arg);
	return (1);
}
