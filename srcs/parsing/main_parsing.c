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

    temp_line = all->line;
    all->lst_cmd = cmd_new(all);
    while (all->line)
    {
        parse_cmd(all);
    }
    all->line = temp_line;
    return ;
}

void    parse_cmd(t_all *all)
{

}
