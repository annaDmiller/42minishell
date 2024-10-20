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

	// show_args(msh);
static	void	test(int tt)
{
	int	i;

	i = -1;

	(void)i;
	(void)tt;
}

void	minishell(t_msh *msh, int argc, char **argv, char **envp)
{
	everyinit(msh, argc, argv, envp);
	parse_cmd_line(msh, argv);
	test(0);
	exec(msh, msh->l_args);
	// exec(msh, cmd);
	// env(msh->env);
	// export(msh, msh->l_args);
	// printf("_______________________________________________\n\n");
	// env(msh->env);
	// export_no_opt(msh);
	// unset(msh, msh->l_args);
	// export_no_opt(msh);
	// pwd(msh);
	// cd(msh, msh->l_args);
	// echo(msh, msh->l_args);
}

int	main(int argc, char **argv, char **envp)
{
	t_msh	msh;

	minishell(&msh, argc, argv, envp);
	freecmdline(msh.l_args);
	free(msh.pwd);
	freenv(msh.env);
	return (0);
}
