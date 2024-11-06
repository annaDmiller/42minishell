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

//function handles line until it reaches the end. To avoid indexes, I move the
//pointer. 
//Therefore, I need temporary var for storing initial pointer - all->temp_l
void	parse_line(t_all *all)
{
	all->temp_l = all->line;
	while (*(all->line))
		add_cmd(all);
	all->line = all->temp_l;
	all->temp_l = NULL;
	return ;
}

//function creates cmd list elements and processes lines cmd by cmd
static void	add_cmd(t_all *all)
{
	t_cmd	*new_el;
	t_cmd	*last_el;

	new_el = cmd_new(all);
	if (!all->lst_cmd)
		all->lst_cmd = new_el;
	else
		cmd_add_el_back(all, new_el);
	last_el = cmd_last_el(all);
	parse_cmd(all, last_el);
	return ;
}
