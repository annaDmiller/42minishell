/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:55 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:55 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int count_len_bfr_ws(char *line)
{
    int ind;

    ind = 0;
    while (line[ind])
    {
        if (!is_white_space(line[ind]))
            return (ind);
        ind++;
    }
    return (ind);
}

int is_redir(char car)
{
    if (car == '>' || car == '<' || car == '|')
        return (0);
    return (1);
}
