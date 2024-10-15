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
#include "../include/minishell.h"

/// @brief if path given argv->arg is not valid it prints pathname: No such file or directory
///	if there is more than one arg it doesnt move and prints cd: too many arguments
////	si on passe en argument ../../include on verifie petit a petit que c'est possible
void    cd(t_msh *msh, t_args *argv)
{
	// char	*tmp;
	// char	*path;
	int	t;

	// tmp = msh->pwd;
	if (!argv) // chdir($home)
	{
		t = chdir(env_retrieve_var(msh->env, "HOME")->var);
		free(msh->pwd);
		msh->pwd = tstrdup(env_retrieve_var(msh->env, "HOME")->var);
		// printf("no path ngl\t\t//t = %d", t);
	}
	else if (argv->next)
		putstrfd("cd: too many arguments\n", STDOUT_FILENO);
		// return (putstrfd("cd: too many arguments\n", STDOUT_FILENO));

	else if (chdir(argv->arg) == 0)
	{
		// printf("going to //\t %s\n", env_retrieve_var(msh->env, "HOME")->var);
		// printf("going to //\t %s\n", argv->arg);
		free(msh->pwd);
		msh->pwd = tstrdup(argv->arg);
		// printf("going to //\t %s\n", env_retrieve_var(msh->env, "HOME")->var);

	}
	else
		printf("cd: %s: No such file or directory\n", argv->arg);
	// reset OLDPWD
}
