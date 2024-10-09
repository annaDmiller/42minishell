/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 08:48:25 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void	minishell(struct msh *msh, int argc, char **argv, char **envp)
{
	everyinit(msh, argc, argv, envp);
	export_alpha(msh);
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
	free(msh.pwd);
	return (0);
}
