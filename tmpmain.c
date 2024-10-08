/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/06 17:40:23 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void	minishell(struct msh *msh, int argc, char **argv, char **env)
{
	// t_env	*tmp;

	envinit(msh, env);
	// tmp = env_retrieve_var(msh->env, "USER");
	// tmp = env_retrieve_var(msh->env, "DOCKER_HOST");
	// tmp = env_retrieve_var(msh->env, "DOCKER_HOSTq");
	// if (tmp)
	// 	printf("%s\n", tmp->var);
	// else
	// 	printf("\n"); // bash --posix printf a \n if the variable doesnt exist && exit(0), no error
	(void)argc;
	(void)argv;
	(void)env;
}

int	main(int argc, char **argv, char **envp)
{
	struct msh	msh;

	minishell(&msh, argc, argv, envp);
	freenv(msh.env);
	(void)argc;
	(void)argv;
	(void)envp;
	// printf("%s\n", fpath_tt("ls", -1));
	return (0);
}
