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

/// @brief cd builtin
int	cd(t_msh *msh, t_args *argv)
{
	t_args	export;

	if (valid_cd(msh, argv)) // if its verified it mean we chdir call has been a success and we changed directory
	{
		export.arg = tjoin(tjoin(tstrdup("OLDPWD"), "="), msh->pwd); // set up OLDPWD env variable to change it with the former pwd
		if (!env_retrieve_var(msh->env, "OLDPWD") && export.arg) // if OLDPWD doesnt exist I export it in the environnement
			export_def(msh, &export);
		if (export.arg)
			free(export.arg); // free the line we allocated to set if OLDPWD didnt exist
		if (env_retrieve_var(msh->env, "OLDPWD")) // if OLDPWD exist
		{
			free(env_retrieve_var(msh->env, "OLDPWD")->var); // free the former pwd it had in variable
			env_retrieve_var(msh->env, "OLDPWD")->var = tstrdup(msh->pwd); // assigning it the former pwd in tstrdup
		}
		if (msh->pwd) // freeing msh->pwd and set it to NULL
		{
			free(msh->pwd);
			msh->pwd = NULL;
		}
		msh->pwd = getcwd(NULL, 0); // updating msh->pwd cause we did chdir
		free(env_retrieve_var(msh->env, "PWD")->var); // free the former pwd it had in variable
		env_retrieve_var(msh->env, "PWD")->var = tstrdup(msh->pwd); // assigning it the new pwd in tstrdup
	}
	else if (argv && argv->arg)
		printf("cd: %s: No such file or directory\n", argv->arg);
	return (1);
}

/// @brief check every cd possibility, if success verifying one it return to process changing env variables and msh->pwd in cd main function
/// @return 1 if it succeed going somewhere with chdir | 0 it there was an error 
int	valid_cd(t_msh *msh, t_args *argv)
{
	if ((argv && argv->next) || (!argv && !env_retrieve_var(msh->env, "HOME"))
		|| (argv && !tstrcmp(argv->arg, "-") && !env_retrieve_var(msh->env, "OLDPWD")))// if cd has not only one argument its an error and we dont chdir anything
	{
		if (argv && argv->next)
			printf("cd: too many arguments\n");
		else if (!argv && !env_retrieve_var(msh->env, "HOME")) // if cd has no arguments it goes to $HOME, if HOME not set printf error and doing nothing
			printf("cd: HOME not set\n");
		else if (argv && !tstrcmp(argv->arg, "-") && !env_retrieve_var(msh->env, "OLDPWD")) // if cd - it goes to $OLDPWD, if OLDPWD not set printf error and doing nothing
			printf("cd: OLDPWD not set\n");
		// msh->exit = 2  // set exit code of the builtin
		return (0);
	}
	if (argv && argv->arg && argv->arg[0] == '~'
		&& expand_wave(msh, argv->arg)) // success chdir in ~/path 
		return (1);
	else if ((argv && !tstrcmp(argv->arg, "-")) // if cd - it goes to $OLDPWD
		&& (env_retrieve_var(msh->env, "OLDPWD")
			&& (!chdir(env_retrieve_var(msh->env, "OLDPWD")->var))))
		return (1);
	else if (!argv && env_retrieve_var(msh->env, "HOME") // if cd has no arguments it goes to $HOME
		&& (!chdir(env_retrieve_var(msh->env, "HOME")->var))) 
		return (1);
	else if (argv->arg && chdir(argv->arg) == 0) // else if chdir the only path given and chdir succeed return 1 to process changing env variables and msh->pwd
		return (1);
	return (0);
}

int	expand_wave(t_msh *msh, char *str)
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
