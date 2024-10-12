#include "../../includes/minishell.h"

char    *handle_output(t_all *all, t_cmd *cmd)
{
    all->line++;
    if (*(all->line) == '>')
        return (output_append(all, cmd), NULL);
    return (output_replace(all, cmd), NULL);
}

static void output_append(t_all *all, t_cmd *cmd)
{
    char    *addr;

    cmd->redir->out_type = 'a';
    all->line++;
    //skip ws
    //read the file to open (can be included into quotes)
    //check if fd != -1, then firstly clear the opened file and close it
    //open the new file and reach its end with get_next_line function
    return ;
}

static void output_replace(t_all *all, t_cmd *cmd)
{
    char    *addr;

    cmd->redir->out_type = 'r';
    //skip ws
    //read the file to open (can be included into quotes)
    //check if fd != -1, then firstly clear the opened file and close it
    //open the new file
    return ;
}