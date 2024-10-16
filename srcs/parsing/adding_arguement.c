/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_arguement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:02 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:03 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int add_arg(t_all *all, t_cmd *cmd, char *arg, int len)
{
    if (!cmd->argv)
        cmd->argv = init_arg(all);
    //add logic for adding the arguement value to the cmd
}
