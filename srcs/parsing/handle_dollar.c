#include "../../includes/minishell.h"

static int  add_env_var(t_all *all, int ind, t_cmd *cmd);

int handle_dollar(t_all *all, int ind, t_cmd *cmd)
{
    if (all->line[ind + 1] == '?')
    {
        cmd->is_last = 1;
        return (ind + 2);
    }
    ind = add_env_var(all, ind, cmd);
    return (ind);
}

static int  add_env_var(t_all *all, int ind, t_cmd *cmd)
{
    char    *env_val;
    char    *env_name;
    int     len_name;
    int     temp;

    len_name = ind + 1;
    while (is_white_space(all->line[len_name]))
        len_name++;
    temp = len_name;
    len_name = temp - ind;
    env_name = (char *) malloc((len_name + 1) * sizeof(char));
    if (!env_name)
        error("handle_dollar: Malloc error\n", all);
    ft_strlcpy(env_name, &(all->line[ind + 1]), len_name + 1);
    env_val = getenv(env_name);
    free(env_name);
    if (!env_val)
        return (temp);
    if (cmd->quote == 0)
        add_arg(all, cmd, env_val, len_name);
    else
        include_env_quote(all, cmd, env_val, len_name);
    return (temp);
}