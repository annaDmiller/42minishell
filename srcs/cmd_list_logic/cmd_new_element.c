/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_new_element.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:55:19 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:55:20 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd   *cmd_new(t_all *all)
{
    t_cmd   *new;

    new = (t_cmd *) malloc(sizeof(t_cmd));
    if (!new)
        error("cmd_new: Malloc error\n", all);
    new->next = NULL;
    new->prev = NULL;
    new->name = NULL;
    new->argv = NULL;
    new->redir = NULL;
    new->is_last = 0;
    new->quote = 0;
    return (new);
}

void    cmd_add_el_back(t_all *all, t_cmd *new_el)
{
    t_cmd   *last;

    last = cmd_last_el(all);
    last->next = new_el;
    new_el->prev = last;
    return ;
}
