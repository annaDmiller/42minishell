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
	if (!all->lst_cmd->next)
		one_exec(msh, all->lst_cmd);
	else
		printf("Double cmd\n");
	test(0);
	(void)i;
	(void)msh;
	(void)all;
}
