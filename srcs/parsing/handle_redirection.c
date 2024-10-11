#include "../../includes/minishell.h"

static void init_redir(t_redir *redir);
static void    handle_pipe(t_all *all, int ind, t_cmd *cmd);

int handle_redir(t_all *all, int ind, t_cmd *cmd)
{
    t_redir *redir;

    redir = (t_redir*) malloc(sizeof(t_redir));
    if (!redir)
        error("handle_redir: Malloc error\n", all);
    init_redir(redir);
    cmd->redir = redir;
    if (all->line[ind] == '>')
        handle_output(all, ind, cmd);
    if (all->line[ind] == '<')
        handle_input(all, ind, cmd);
    if (all->line[ind] == '|')
        handle_pipe(all, ind++, cmd);
    return (ind);
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
    return ;
}

static void    handle_pipe(t_all *all, int ind, t_cmd *cmd)
{
    cmd->redir->is_pipe = '1';
    return ;
}

