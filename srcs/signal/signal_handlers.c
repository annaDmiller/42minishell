/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:48:44 by amelniko          #+#    #+#             */
/*   Updated: 2024/11/14 10:48:45 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/signal.h"

void	sigint_hdl_parent(int sig)
{
	g_sig = sig;
	ft_printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	ign_handler(int sig)
{
	g_sig = sig;
	printf("\n");
	return ;
}

void	heredoc_handler(int sig)
{
	if (ioctl(STDIN_FILENO, TIOCSTI, "\n") == -1)
		return ;
	g_sig = sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	return ;
}
