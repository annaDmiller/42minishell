/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_logic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:55:43 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:55:44 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	error(char *mess, t_all *all, int sig)
{
	ft_putstr_fd("Error [", 2);
	ft_putstr_fd(mess, 2);
	ft_putstr_fd("]", 2);
	if (sig == SIGTERM)
	{
		ft_putchar_fd('\n', 2);
		all->msh->have_to_exit = 1;
		free_exit(all, all->msh, 1);
	}
	if (sig == SIGINT)
	{
		while (*all->line)
			all->line++;
		all->err = 1;
		return ;
	}
	kill(getpid(), sig);
	return ;
}
