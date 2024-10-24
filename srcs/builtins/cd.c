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

/// @brief if path given argv->arg is not valid it prints pathname: No such file or directory
///	if there is more than one arg it doesnt move and prints cd: too many arguments
////	si on passe en argument ../../include on verifie petit a petit que c'est possible
void	cd(t_msh *msh, t_args *argv)
{
	if (!argv && !env_retrieve_var(msh->env, "HOME"))
		fprintf(stderr, "cd: HOME not set\n");
	else if (!argv && chdir(env_retrieve_var(msh->env, "HOME")->var) == 0) // chdir($home)
	{
		// proteger si OLDPWD n'existe pas
		free(env_retrieve_var(msh->env, "OLDPWD")->var);
		env_retrieve_var(msh->env, "OLDPWD")->var = tstrdup(msh->pwd);
		free(msh->pwd);
		msh->pwd = NULL;
		msh->pwd = getcwd(NULL, 0);
	}
	else if (argv->next)
		putstrfd("cd: too many arguments\n", STDOUT_FILENO);
	else if (chdir(argv->arg) == 0)
	{
		free(env_retrieve_var(msh->env, "OLDPWD")->var);
		env_retrieve_var(msh->env, "OLDPWD")->var = tstrdup(msh->pwd);
		free(msh->pwd);
		msh->pwd = NULL;
		msh->pwd = getcwd(NULL, 0);
	}
	else
		fprintf(stderr, "cd: %s: No such file or directory\n", argv->arg);
}
