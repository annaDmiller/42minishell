#include "../../includes/minishell.h"

int    handle_output(t_all *all, int ind, t_cmd *cmd)
{
    if (all->line[++ind] == '>')
        ind = output_append(all, ind, cmd);
    else
        ind = output_replace(all, ind, cmd);
    return (ind);
}

static int  output_append(t_all *all, int ind, t_cmd *cmd)
{
    cmd->redir->out_type = 'a';
    //skip ws
    //read the file to open (can be included into quotes)
    //check if fd != -1, then firstly clear the opened file and close it
    //open the new file and reach its end with get_next_line function
    return (ind);
}

static int  output_replace(t_all *all, int ind, t_cmd *cmd)
{
    cmd->redir->out_type = 'r';
    //skip ws
    //read the file to open (can be included into quotes)
    //check if fd != -1, then firstly clear the opened file and close it
    //open the new file
    return (ind);
}