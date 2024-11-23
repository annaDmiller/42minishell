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

int	cd(t_msh *msh, t_args *argv, int tzy)
{
	tzy = valid_cd(msh, argv);
	if (tzy == 1)
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
	if (tzy == 2 && argv && argv->arg && (((!(!argv->arg[1]
						&& (argv->arg[0] == '-'))) && argv->arg[0] != '~')))
	{
		if (curr_dir() && dir_check(argv->arg) == 0)
			err_msg("cd", argv->arg, "Not a directory\n");
		else if (!curr_dir() || dir_check(argv->arg) == 2)
			err_msg("cd", argv->arg, "No such file or directory\n");
	}
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
			putstderr("cd: too many arguments\n");
		else if (!argv && !env_retrieve_var(msh->env, "HOME"))
			putstderr("cd: HOME not set\n");
		else if (argv && !tstrcmp(argv->arg, "-")
			&& !env_retrieve_var(msh->env, "OLDPWD"))
			putstderr("cd: OLDPWD not set\n");
		return (0);
	}
	if ((argv && argv->arg && chdir(argv->arg) == 0)
		|| ((argv && argv->arg && !tstrcmp(argv->arg, "-"))
			&& (env_retrieve_var(msh->env, "OLDPWD")
				&& (!chdir(env_retrieve_var(msh->env, "OLDPWD")->var))))
		|| (!argv && env_retrieve_var(msh->env, "HOME")
			&& env_retrieve_var(msh->env, "HOME")->var
			&& (!chdir(env_retrieve_var(msh->env, "HOME")->var)))
		|| (argv && argv->arg && argv->arg[0] == '~' && wave(msh, argv->arg)))
		return (1);
	return (2);
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
		putstderr("cd: Couldn't retrieve home path\n");
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
	err_msg("cd", path, "No such file or directory\n");
	free(path);
	return (0);
}
