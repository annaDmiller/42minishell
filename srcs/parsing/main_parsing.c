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

void    parse_line(t_all *all)
{
    char    *temp_line;
    t_cmd   *last;

    temp_line = all->line;
    while (all->line)
    {
        add_cmd(all);
        last = cmd_last_el(all);
        if (last->is_last)
            break ;
    }
    all->line = temp_line;
    return ;
}

void    add_cmd(t_all *all)
{
    t_cmd   *new_el;

    new_el = cmd_new(all);
    if (!all->lst_cmd)
        all->lst_cmd = new_el;
    else
        cmd_add_el_back(all, new_el);
    parse_cmd(all);
}
