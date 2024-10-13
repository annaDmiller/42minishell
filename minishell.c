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
#include "include/structures.h"



void	minishell(t_msh *msh, int argc, char **argv, char **envp)
{
	everyinit(msh, argc, argv, envp);
	parse_cmd_line(msh, argv);
	export_def(msh, msh->l_args);
	// env(msh->env);
	export_no_opt(msh);
	(void)argc;
	(void)argv;
	(void)envp;
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	minishell(&msh, argc, argv, envp);
	freecmdline(msh.l_args);
	freenv(msh.env);
	free(msh.pwd);
	return (0);
}
