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

static	int	expand_wave(t_msh *msh, char *str);
static	int	valid_cd(t_msh *msh, t_args *argv);

int	cd(t_msh *msh, t_args *argv)
{
	t_args	export;

	if (valid_cd(msh, argv))
	{
		export.arg = tjoin(tjoin(tstrdup("OLDPWD"), "="), msh->pwd);
		if (!env_retrieve_var(msh->env, "OLDPWD"))
			export_def(msh, &export);
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
		free(env_retrieve_var(msh->env, "PWD")->var);
		env_retrieve_var(msh->env, "PWD")->var = tstrdup(msh->pwd);
	}
	else
		printf("cd: %s: No such file or directory\n", argv->arg);
	return (1);
}

static	int	valid_cd(t_msh *msh, t_args *argv)
{
	if (argv && argv->next)
	{
		printf("cd: too many arguments\n");
		return (0);
	}
	else if (!argv && !env_retrieve_var(msh->env, "HOME"))
	{
		printf("cd: HOME not set\n");
		return (0);
	}
	if (argv && argv->arg && argv->arg[0] == '~'
		&& !expand_wave(msh, argv->arg))
		return (0);
	else if ((argv && !tstrcmp(argv->arg, "-"))
		&& (env_retrieve_var(msh->env, "OLDPWD")
			&& (!chdir(env_retrieve_var(msh->env, "OLDPWD")->var))))
		return (0);
	else if (!argv && env_retrieve_var(msh->env, "HOME")
		&& (!chdir(env_retrieve_var(msh->env, "HOME")->var)))
		return (0);
	else if (argv->arg && chdir(argv->arg) == 0)
		return (0);
	return (1);
}

static	int	expand_wave(t_msh *msh, char *str)
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
		return (0);
	}
	free(path);
	return (1);
}
