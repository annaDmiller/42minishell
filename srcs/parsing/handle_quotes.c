#include "../../includes/minishell.h"

char    *handle_quotes(t_all *all, t_cmd *cmd)
{
    if (*(all->line++) == '"' && cmd->quote != 1)
        return (handle_double_quotes(all, cmd));
    return (handle_single_quote(all, cmd));
    }

char    *handle_double_quotes(t_all *all, t_cmd *cmd)
{
    char    *str;
    int     ind;
    int     len;

    ind =  0;
    cmd->quote = 2;
    str = NULL;
    while (all->line[ind])
    {
        if (all->line[ind] == '"')
            break ;
        if (all->line[ind] != '\'')
            len++;
        ind++;
    }
    str = (char *) malloc(sizeof(char) * (len + 1));
    if (!str)
        error("handle_doub_quotes: Malloc error\n", all);
    copy_without_car(str, all->line, len + 1, "\'");
    cmd->quote = 0;
    all->line += ind;
    return (str);
}

void copy_without_car(char *dest, char *src, int size, char car)
{
    int ind;
    int add_ind;

    ind = -1;
    add_ind = 0;
    while (++ind < size - 1 && src[ind + add_ind])
    {
        if (src[ind + add_ind] != car)
            dest[ind] = src[ind];
        else
            add_ind++;
        ind++;
    }
    dest[ind] = '\0';
    return ;
}
