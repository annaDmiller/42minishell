/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:55:01 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:55:03 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int is_empty_line(char *cmd_line)
{
    int ind;

    ind = 0;
    while (cmd_line[ind])
    {
        if (is_white_space(cmd_line[ind]))
            return (1);
        ind++;
    }
    return (0);
}

int  is_white_space(char car)
{
    if (car == ' ' || car == '\v' || car == '\t' || car == '\r'
        || car == '\f' || car == '\n')
        return (0);
    return (1);
}

int is_quote(char car)
{
    if (car == '\'' || car == '"')
        return (0);
    return (1);
}

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
