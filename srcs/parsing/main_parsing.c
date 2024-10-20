/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:15:54 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/06 20:15:54 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	add_cmd(t_all *all);

void	parse_line(t_all *all)
{
	all->temp_l = all->line;
	while (*(all->line))
		add_cmd(all);
	all->line = all->temp_l;
	all->temp_l = NULL;
	return ;
}

static void	add_cmd(t_all *all)
{
	t_cmd	*new_el;

	new_el = cmd_new(all);
	if (!all->lst_cmd)
		all->lst_cmd = new_el;
	else
		cmd_add_el_back(all, new_el);
	parse_cmd(all);
	return ;
}
