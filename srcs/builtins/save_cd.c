save_cd.c


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
	t_args	oldpwd;

	if (argv && argv->next)
		printf("cd: too many arguments\n");
	else if (!argv && !env_retrieve_var(msh->env, "HOME"))
		printf("cd: HOME not set\n");
	else if (argv && !tstrcmp(argv->arg, "-"))
		if (env_retrieve_var(msh->env, "OLDPWD") && (chdir(env_retrieve_var(msh->env, "OLDPWD")->var)))
			export

	else if ((!argv && chdir(env_retrieve_var(msh->env, "HOME")->var) == 0)
			|| (argv->arg && chdir(argv->arg) == 0))
	{
		if (!env_retrieve_var(msh->env, "OLDPWD"))
		{
			oldpwd.arg = tjoin(tjoin(tstrdup("OLDPWD"), "="), msh->pwd);
			export_def(msh, &oldpwd);
		}
		else if (env_retrieve_var(msh->env, "OLDPWD"))
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
		free(env_retrieve_var(msh->env, "PWD")->var);
		env_retrieve_var(msh->env, "PWD")->var = tstrdup(msh->pwd);
	}
	else
		printf("cd: %s: No such file or directory\n", argv->arg);
	return (1);
}
