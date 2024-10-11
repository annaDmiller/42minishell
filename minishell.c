/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/11 00:53:24 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void	minishell(struct msh *msh, int argc, char **argv, char **envp)
{
	everyinit(msh, argc, argv, envp);
//	export_def(msh, argv[1]);
//	env(msh);
//	unset(msh, argv[1]);
	(void)argc;
	(void)argv;
	(void)envp;
}

void	freestr(char *str)
{
	free(str);
}

int	main(int argc, char **argv, char **envp)
{
	struct msh	msh;

	minishell(&msh, argc, argv, envp);
	freenv(msh.env);
	free(msh.pwd);
	return (0);
}
