#include "../../includes/minishell.h"

int handle_quotes(t_all *all, int ind, t_cmd *cmd, char *act)
{
    if (all->line[ind] == '"')
        ind = handle_double_quotes(all, ind, cmd, act);
    else
        ind = handle_single_quote(all, ind, cmd, act);
    return (ind);
}

int handle_double_quotes(t_all *all, int ind, t_cmd *cmd, char *act)
{
    cmd->quote = 2;
    //reading line until another double quote is met
    //if there is a dollar sign, then the env var value must be replaced instead of the 
    cmd->quote = 0;
    return (ind);
}

int handle_single_quotes(t_all *all, int ind, t_cmd *cmd, char *act)
{
    cmd->quote = 1;
    //reading line until another single quote is met
    //add line as an arguement to the list of arguements
    cmd->quote = 0;
    return (ind);
}

void    include_env_quote(t_all *all, t_cmd *cd, char *env_val, int len_env)
{
    //add logic to add the env_value to the current string for arguement inside the quotes sentence
    return ;
}