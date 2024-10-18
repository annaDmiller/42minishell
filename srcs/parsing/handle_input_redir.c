/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:15 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:16 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void read_from_stdin(t_all *all, t_cmd *cmd);
static void input_from_stdin(t_all *all, t_cmd *cmd);
static void input_from_file(t_all *all, t_cmd *cmd);
static char *read_keyword(t_all *all, t_cmd *cmd);

char    *handle_input(t_all *all, t_cmd *cmd)
{
    all->line++;
    if (*(all->line) == '<')
        return (input_from_stdin(all, cmd), NULL);
    return (input_from_file(all, cmd), NULL);
}

static void input_from_stdin(t_all *all, t_cmd *cmd)
{
    char    *temp;

    all->line++;
    all->temp_for_free = read_keyword(all, cmd);
    if (cmd->redir->fd_infile != -2)
    {
        close(cmd->redir->fd_infile);
        if (cmd->redir->in_txt)
            free(cmd->redir->in_txt);
    }
    temp = all->temp_for_free;
    all->temp_for_free = ft_strjoin(temp, "\n");
    free(temp);
    if (!all->temp_for_free)
        error("input_from_stdin: Malloc error\n", all);
    read_from_stdin(all, cmd);
    free(all->temp_for_free);
    all->temp_for_free = NULL;
    cmd->redir->in_type = 's';
    cmd->redir->fd_infile = 0;
    return ;
}

static void input_from_file(t_all *all, t_cmd *cmd)
{
    char    *addr;
    
    addr = read_addr(all, cmd);
    if (!addr)
        error("input_redir: syntax error\n", all);
    if (cmd->redir->fd_infile != -2)
        close(cmd->redir->fd_infile);
    cmd->redir->fd_infile = open(addr, O_RDONLY);
    if (cmd->redir->fd_infile == -1)
        error("input_from_file: impossible to open file\n", all);
    cmd->redir->in_type = 'f';
    free(addr);
    return ;
}

static void read_from_stdin(t_all *all, t_cmd *cmd)
{
    char    *gnl;
    char    *temp;

    temp = NULL;
    ft_printf("> ");
    gnl = get_next_line(0);
    if (!gnl)
        error("read_from_stdin: Malloc error\n", all);
    while (ft_strncmp(all->temp_for_free, gnl, ft_strlen(all->temp_for_free) + 1))
    {
        temp = cmd->redir->in_txt;
        cmd->redir->in_txt = ft_strjoin(temp, gnl);
        free(temp);
        free(gnl);
        if (!cmd->redir->in_txt)
            error("read_from_stdin: Malloc error\n", all);
        ft_printf("> ");
        gnl = get_next_line(0);
    }
    free(gnl);
    return ;
}

static char *read_keyword(t_all *all, t_cmd *cmd)
{
    char    *temp;
    char    *ret;

    all->temp_for_free = NULL;
    ret = NULL;
    while (!is_white_space(*(all->line)) && *(all->line))
        all->line++;
    if (!is_redir(*(all->line)))
        return (NULL);
    while (is_white_space(*(all->line)) && *(all->line))
    {
        if (!is_quote(*(all->line)))
            all->temp_for_free = handle_quotes(all, cmd);
        else
            all->temp_for_free = handle_word(all, cmd, 1);
        temp = ret;
        ret = ft_strjoin(temp, all->temp_for_free);
        if (!ret)
            error("read_addr: Malloc error\n", all);
        free(temp);
        free(all->temp_for_free);
    }
    all->temp_for_free = NULL;
    return (ret);
}