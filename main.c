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

void	minishell(struct msh *msh, int argc, char **argv, char **envp)
{
	// t_env	*tmp;
	everyinit(msh, argc, argv, envp);
	(void)argc;
	(void)argv;
	(void)envp;
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
