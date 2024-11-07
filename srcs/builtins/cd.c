/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:16 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/07 01:38:48 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	void	reset_pwd(t_msh *msh);
static	void	reset_oldpwd(t_msh *msh);

int	cd(t_msh *msh, t_args *argv)
{
	if (valid_cd(msh, argv))
	{
		reset_oldpwd(msh);
		if (msh->pwd)
			free(msh->pwd);
		msh->pwd = NULL;
		msh->pwd = getcwd(NULL, 0);
		reset_pwd(msh);
		msh->exit = EXIT_SUCCESS;
		if (argv && argv->arg && argv->arg[0] == '-' && !argv->arg[1])
			printf("%s\n", msh->pwd);
		return (1);
	}
	if (argv && argv->arg)
		if ((!(!argv->arg[1] && (argv->arg[0] == '-'))) && argv->arg[0] != '~')
			printf("cd: %s: No such file or directory\n", argv->arg);
	msh->exit = EXIT_FAILURE;
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
		return (0);
	}
	if ((argv && argv->arg && chdir(argv->arg) == 0)
		|| ((argv && argv->arg && !tstrcmp(argv->arg, "-"))
			&& (env_retrieve_var(msh->env, "OLDPWD")
				&& (!chdir(env_retrieve_var(msh->env, "OLDPWD")->var))))
		|| (!argv && env_retrieve_var(msh->env, "HOME")
			&& (!chdir(env_retrieve_var(msh->env, "HOME")->var)))
		|| (argv && argv->arg && argv->arg[0] == '~' && wave(msh, argv->arg)))
		return (1);
	return (0);
}

static	void	reset_pwd(t_msh *msh)
{
	t_args	export;

	export.arg = tjoin(tjoin(tstrdup("PWD"), "="), msh->pwd);
	if (env_retrieve_var(msh->env, "PWD"))
	{
		if (env_retrieve_var(msh->env, "PWD")->var)
			free(env_retrieve_var(msh->env, "PWD")->var);
		env_retrieve_var(msh->env, "PWD")->var = tstrdup(msh->pwd);
	}
	if (export.arg)
		free(export.arg);
}

static	void	reset_oldpwd(t_msh *msh)
{
	t_args	export;

	export.arg = tjoin(tjoin(tstrdup("OLDPWD"), "="), msh->pwd);
	if (env_retrieve_var(msh->env, "OLDPWD"))
	{
		if (env_retrieve_var(msh->env, "OLDPWD")->var)
			free(env_retrieve_var(msh->env, "OLDPWD")->var);
		env_retrieve_var(msh->env, "OLDPWD")->var = tstrdup(msh->pwd);
	}
	if (export.arg)
		free(export.arg);
}

int	wave(t_msh *msh, char *str)
{
	char	*path;

	if (!msh->home)
	{
		printf("cd: Couldn't retrieve home path\n");
		return (0);
	}
	path = NULL;
	if (str && str[0] == '~')
		str++;
	path = tjoin(tstrdup(msh->home), str);
	if (path && !chdir(path))
	{
		free(path);
		return (1);
	}
	printf("cd: %s: No such file or directory\n", path);
	free(path);
	return (0);
}
