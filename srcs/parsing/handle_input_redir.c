#include "../../includes/minishell.h"

int    handle_input(t_all *all, int ind, t_cmd *cmd)
{
    if (all->line[++ind] == '<')
        ind = input_from_stdin(all, ind, cmd);
    else
        ind = input_from_file(all, ind, cmd);
    return (ind);
}

static int input_from_stdin(t_all *all, int ind, t_cmd *cmd)
{
    cmd->redir->in_type = 's';
    //skip ws
    //read the keyword to stop reading (keyword can be included into quotes)
    //read from stdin with get_next_line until the keyword is met (str_realloc + cycle) - + print "> " before input line
    //add the read 
    return (ind);
}

static int input_from_file(t_all *all, int ind, t_cmd *cmd)
{
    cmd->redir->in_type = 'f';
    //skip ws
    //read the file name (can be included into quotes)
    //check, if fd != -1, then you need to firstly close the previous file
    //open the new file and update the fd in cmd
    return (ind);
}