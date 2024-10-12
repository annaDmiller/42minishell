#include "../../includes/minishell.h"

static char *finish_single_quote(t_all *all, t_cmd *cmd, char **str);

char    *handle_single_quotes(t_all *all, t_cmd *cmd)
{
    char    *str;
    int     ind;
    int     len;
    char    *temp;
    char    *tail;

    ind =  0;
    if (cmd->quote == 0)
        cmd->quote = 1;
    str = NULL;
    while (all->line[ind])
    {
        if (all->line[ind] == '\'' || all->line[ind] == '$')
            break ;
        if (all->line[ind] != '"')
            len++;
        ind++;
    }
    str = (char *) malloc(sizeof(char) * (len + 1));
    if (!str)
        error("handle_sing_quotes: Malloc error\n", all);
    copy_without_car(str, all->line, len + 1, '"');
    if (all->line[ind] == '\'')        
        cmd->quote = 0;
    all->line += ind;
    return (finish_single_quote(all, cmd, &str));
    //reading line until another single quote is met
    //if there is a dollar sign, then the env var value must be input
    //if double quote - ignore it and go on if only it's not $ after that 
    //add line as an arguement to the list of arguements
}

static char *finish_single_quote(t_all *all, t_cmd *cmd, char **str)
{
    char    *tail;
    char    *temp;

    if (*(all->line) == '$')
        add_env_var(all, cmd, str);
    if (cmd->quote)
    {
        tail = handle_single_quotes(all, cmd);
        temp = *str;
        *str = ft_strjoin(temp, tail);
        free(tail);
        free(temp);
        if (!*str)
            error("handle_sing_quotes: ft_strjoin error\n", all);
    }
    return (*str);
}

static void add_env_var(t_all *all, t_cmd *cmd, char **str)
{
    //add logic which adds env var taken after dollar to the string str
    return ;
}