/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:42 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:43 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char *take_str(t_all *all, t_cmd *cmd);
static void add_cmd_name(t_all *all, t_cmd *last);

void    parse_cmd(t_all *all)
{
    t_cmd   *last;
    char    *str;
    char    *temp;
    char    *temp1;
    char    *test;

    last = cmd_last_el(all);
    str = NULL;
    while (*(all->line) || str)
    {
        test = all->line;
        if (!is_white_space(*(all->line)) && str && last->quote == 0)
            add_arg(all, last, &str);
        if (*all->line == '\0')
            break ;
        while (!is_white_space(*(all->line)) && last->quote == 0)
        {
            str = NULL;
            all->line++;
        }
        if (str)
        {
            temp = take_str(all, last);
            temp1 = str;
            str = ft_strjoin(temp1, temp);
            free(temp);
            free(temp1);
            if (!str)
                error("parse_cmd: Malloc error\n", all);
        }
        else
            str = take_str(all, last);
    }
    return ;
}

static char *take_str(t_all *all, t_cmd *cmd)
{
    char    *str;

    if (!cmd->name)
    {
        if (*(all->line) != '$')
            add_cmd_name(all, cmd);
        else
            cmd->name = handle_dollar(all, cmd, 0);
        return (NULL);
    }
    if (*(all->line) == '$' && is_white_space(*(all->line + 1)) && *(all->line + 1))
        return (handle_dollar(all, cmd, 0));
    if (!is_quote(*(all->line)))
        return (handle_quotes(all, cmd));
    if (!is_redir(*(all->line)))
        return (handle_redir(all, cmd));
    return (handle_word(all, cmd, 0));
}

static void add_cmd_name(t_all *all, t_cmd *last)
{
    int     len_name;
    char    *cmd_name;

    len_name = 0;
    while (is_white_space(all->line[len_name]) && all->line[len_name])
        len_name++;
    cmd_name = (char *) malloc((len_name + 1) * sizeof(char));
    if (!cmd_name)
        error("add_cmd_name: Malloc error\n", all);
    ft_strlcpy(cmd_name, all->line, len_name + 1);
    last->name = cmd_name;
    all->line += len_name;
    return ;
    //rewrite logic for len_name?
}
