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

void	sigint_hdl_child(int sig)
{
	g_sig = sig;
	return ;
}

void	ign_handler(int sig)
{
	g_sig = sig;
	printf("\n");
	return ;
}
