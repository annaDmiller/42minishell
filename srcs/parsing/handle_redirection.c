/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:34 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:35 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void init_redir(t_redir *redir);
static void handle_pipe(t_all *all, t_cmd *cmd);

char    *handle_redir(t_all *all, t_cmd *cmd)
{
    t_redir *redir;
    char    *str;

    redir = (t_redir*) malloc(sizeof(t_redir));
    if (!redir)
        error("handle_redir: Malloc error\n", all);
    init_redir(redir);
    cmd->redir = redir;
    str = NULL;
    if (*(all->line) == '>')
        handle_output(all, cmd);
    if (*(all->line) == '<')
        str = handle_input(all, cmd);
    if (*(all->line) == '|')
        handle_pipe(all, cmd);
    return (str);
}

static void init_redir(t_redir *redir)
{
    redir->is_pipe = 0;
    redir->fd_infile = -1;
    redir->fd_outfile = -1;
    redir->in_type = '0';
    redir->out_type = '0';
    redir->pipe_fd[0] = -1;
    redir->pipe_fd[1] = -1;
    redir->in_txt = NULL;
    return ;
}

static void    handle_pipe(t_all *all, t_cmd *cmd)
{
    cmd->redir->is_pipe = 'y';
    return ;
}

