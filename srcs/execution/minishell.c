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
#include "../../includes/minishell.h"

	// show_args(msh);
static	void	test(int tt)
{
	int	i;

	i = -1;

	(void)i;
	(void)tt;
}

void	minishell(t_all *all, t_msh *msh)
{
	int	i;

	i = 0;
	exec(msh, all->lst_cmd);
	test(0);
	(void)i;
	(void)msh;
	(void)all;
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_msh	msh;

// 	minishell(&msh, argc, argv, envp);
// 	freecmdline(msh.l_args);
// 	free(msh.pwd);
// 	freenv(msh.env);
// 	return (0);
// }
