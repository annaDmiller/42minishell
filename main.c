/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 03:28:50 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void	minishell(struct msh *msh, int argc, char **argv, char **env)
{
	// t_env	*tmp;
	envinit(msh, env);
	// tmp = env_retrieve_var(msh->env, "DISPLAY");
	// tmp = env_retrieve_var(msh->env, "USER");
	// if (tmp)
	// 	printf("%s\n", tmp->var);
	// else
	// 	printf("\n"); // bash --posix printf a \n at the end of everything it had to write && exit(0), no error
	(void)argc;
	(void)argv;
	(void)env;
}

int	main(int argc, char **argv, char **envp)
{
	struct msh	msh;

	minishell(&msh, argc, argv, envp);
	(void)argc;
	(void)argv;
	(void)envp;
	freenv(msh.env);
	return (0);
}
