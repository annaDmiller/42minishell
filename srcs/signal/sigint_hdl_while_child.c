/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint_hdl_while_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:48:37 by amelniko          #+#    #+#             */
/*   Updated: 2024/11/14 10:48:39 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

struct sigaction	*sigint_ign_wait(t_all *all)
{
	struct sigaction	*old_act;
	struct sigaction	new_act;

	new_act.sa_handler = ign_handler;
	new_act.sa_flags = 0;
	sigemptyset(&new_act.sa_mask);
	old_act = (struct sigaction *) malloc(sizeof(struct sigaction));
	if (!old_act)
		error("ign_signal: malloc error", all, SIGTERM);
	if (sigaction(SIGINT, &new_act, old_act) == -1)
		error("ign_signal: sigaction error", all, SIGTERM);
	return (old_act);
}

void	restore_sigint_hdl(t_all *all, struct sigaction *old_act)
{
	if (sigaction(SIGINT, old_act, NULL) == -1)
		error("restore_signal: sigaction error", all, SIGTERM);
	free(old_act);
	return ;
}
