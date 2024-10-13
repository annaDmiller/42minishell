/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_last_element.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:55:13 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:55:14 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_cmd   *cmd_last_el(t_all *all)
{
    t_cmd   *last;

    last = all->lst_cmd;
    while (last->next)
        last = last->next;
    return (last);
}
