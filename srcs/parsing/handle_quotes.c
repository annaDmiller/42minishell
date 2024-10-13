#include "../../includes/minishell.h"

static char *add_tail_until_finish(t_all *all, t_cmd *cmd, char **head);
static void check_ending(t_all *all, t_cmd *cmd);

char    *handle_quotes(t_all *all, t_cmd *cmd)
{
    if (*(all->line++) == '"')
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
    len = 0;
    while (all->line[ind])
    {
        if (all->line[ind] == '"')
            break ;
        if (all->line[ind] == '$')
            if (is_white_space(all->line[ind + 1]))
                break ;
        len++;
        ind++;
    }
    str = (char *) malloc(sizeof(char) * (len + 1));
    if (!str)
        error("handle_doub_quotes: Malloc error\n", all);
    ft_strlcpy(str, all->line, len + 1);
    all->line += ind;
    check_of_ending(all, cmd);
    if (cmd->quote)
        return (add_tail_until_finish(all, cmd, &str));
    return (str);
}

char    *handle_single_quotes(t_all *all, t_cmd *cmd)
{
    char    *str;
    int     ind;
    int     len;

    ind =  0;
    cmd->quote = 1;
    len = 0;
    while (all->line[ind])
    {
        if (all->line[ind] == '\'')
            break ;
        len++;
        ind++;
    }
    str = (char *) malloc(sizeof(char) * (len + 1));
    if (!str)
        error("handle_sing_quotes: Malloc error\n", all);
    ft_strlcpy(str, all->line, len + 1);
    cmd->quote = 0;
    all->line += ind + 1;
    return (str);
}

static void check_ending(t_all *all, t_cmd *cmd)
{
    if (all->line == '"')
    {
        cmd->quote = 0;
        all->line++;
    }
    return ;
}

static char *add_tail_until_finish(t_all *all, t_cmd *cmd, char **head)
{
    char    *env_val;
    char    *tail;
    char    *temp;

    all->temp_for_free = *head;
    env_val = handle_dollar(all, cmd, '"');
    *head = ft_strjoin(all->temp_for_free, env_val);
    free(all->temp_for_free);
    free(env_val);
    if (!(*(all->line)))
        return (*head);
    all->temp_for_free = *head;
    tail = handle_double_quotes(all, cmd);
    *head = ft_strjoin(all->temp_for_free, tail);
    free(tail);
    free(all->temp_for_free);
    all->temp_for_free = NULL;
    return (*head);
}
