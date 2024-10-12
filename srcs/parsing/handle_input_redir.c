#include "../../includes/minishell.h"

char    *handle_input(t_all *all, t_cmd *cmd)
{
    all->line++;
    if (*(all->line) == '<')
        return (input_from_stdin(all, cmd));
    return (input_from_file(all, cmd), NULL);
}

static char *input_from_stdin(t_all *all, t_cmd *cmd)
{
    char    *str;
    char    *keyword;
    char    *line;

    cmd->redir->in_type = 's';
    all->line++;
    //skip ws
    //read the keyword to stop reading (keyword can be included into quotes)
    //read from stdin with get_next_line until the keyword is met (str_realloc + cycle) - + print "> " before input line
    //add the read 
    return (str);
}

static void input_from_file(t_all *all, t_cmd *cmd)
{
    char    *addr;
    
    cmd->redir->in_type = 'f';
    //skip ws
    //read the file name (can be included into quotes)
    //check, if fd != -1, then you need to firstly close the previous file
    //open the new file and update the fd in cmd
    return ;
}