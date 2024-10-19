/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 13:28:25 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/19 13:28:27 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_args	*arg_new(t_all *all)
{
	t_args	*argv;

	argv = (t_args*) malloc(sizeof(t_args));
	if (!argv)
		error("init_arg: Malloc error\n", all);
	argv->arg = NULL;
	argv->next = NULL;
	argv->prev = NULL;
	return (argv);
}

void	arg_add_el_back(t_cmd *last_cmd, t_args *new_el)
{
	t_args	*last;

	last = arg_last_el(last_cmd);
	last->next = new_el;
	new_el->prev = last;
	return ;
}

t_args	*arg_last_el(t_cmd *last_cmd)
{
	t_args	*last;

	last = last_cmd->argv;
	while (last->next)
		last = last->next;
	return (last);
}
