/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:16 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/06 22:14:57 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	void	reset_pwd(t_msh *msh);
static	void	reset_oldpwd(t_msh *msh);

int	cd(t_msh *msh, t_args *argv)
{
	t_args	export;

	if (valid_cd(msh, argv))
	{
		reset_pwd(msh);
		if (msh->pwd)
			free(msh->pwd);
		msh->pwd = NULL;
		msh->pwd = getcwd(NULL, 0);
		reset_oldpwd(msh);
		msh->exit = 0;
		return (1);
	}
	if (argv && argv->arg)
		printf("cd: %s: No such file or directory\n", argv->arg);
	msh->exit = 1;
	return (1);
}

int	valid_cd(t_msh *msh, t_args *argv)
{
	if ((argv && argv->next) || (!argv && !env_retrieve_var(msh->env, "HOME"))
		|| (argv && argv->arg && !tstrcmp(argv->arg, "-")
			&& !env_retrieve_var(msh->env, "OLDPWD")))
	{
		if (argv && argv->next)
			printf("cd: too many arguments\n");
		else if (!argv && !env_retrieve_var(msh->env, "HOME"))
			printf("cd: HOME not set\n");
		else if (argv && !tstrcmp(argv->arg, "-")
			&& !env_retrieve_var(msh->env, "OLDPWD"))
			printf("cd: OLDPWD not set\n");
		msh->exit = 1;
		return (0);
	}
	if ((argv && argv->arg && argv->arg[0] == '~' && wave(msh, argv->arg))
		|| ((argv && argv->arg && !tstrcmp(argv->arg, "-"))
			&& (env_retrieve_var(msh->env, "OLDPWD")
				&& (!chdir(env_retrieve_var(msh->env, "OLDPWD")->var))))
		|| (!argv && env_retrieve_var(msh->env, "HOME")
			&& (!chdir(env_retrieve_var(msh->env, "HOME")->var)))
		|| (argv && argv->arg && chdir(argv->arg) == 0))
		return (1);
	return (0);
}

static	void	reset_pwd(t_msh *msh)
{
	t_args	export;

	export.arg = tjoin(tjoin(tstrdup("OLDPWD"), "="), msh->pwd);
	if (!env_retrieve_var(msh->env, "OLDPWD") && export.arg)
		export_def(msh, &export);
	else if (env_retrieve_var(msh->env, "OLDPWD"))
	{
		free(env_retrieve_var(msh->env, "OLDPWD")->var);
		env_retrieve_var(msh->env, "OLDPWD")->var = tstrdup(msh->pwd);
	}
	if (export.arg)
		free(export.arg);
}

static	void	reset_oldpwd(t_msh *msh)
{
	t_args	export;

	export.arg = tjoin(tjoin(tstrdup("PWD"), "="), msh->pwd);
	if (!env_retrieve_var(msh->env, "PWD") && export.arg)
		export_def(msh, &export);
	else if (env_retrieve_var(msh->env, "OLDPWD"))
	{
		free(env_retrieve_var(msh->env, "PWD")->var);
		env_retrieve_var(msh->env, "PWD")->var = tstrdup(msh->pwd);
	}
	if (export.arg)
		free(export.arg);
}

int	wave(t_msh *msh, char *str)
{
	char	*path;

	if (str && str[0] == '~')
		str++;
	path = tjoin(tstrdup(env_retrieve_var(msh->env, "HOME")->var), str);
	if (!path)
		return (0);
	if (!chdir(path))
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}
