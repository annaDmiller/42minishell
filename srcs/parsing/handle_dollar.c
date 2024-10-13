#include "../../includes/minishell.h"

static char *add_env_var(t_all *all, t_cmd *cmd);

char    *handle_dollar(t_all *all, t_cmd *cmd)
{
    all->line++;
// what is last exit foreground exit status???
//    if (*(++all->line) == '?')
//    {
//        return (NULL);
//    }
    return (add_env_var(all, cmd));
}

static char *add_env_var(t_all *all, t_cmd *cmd)
{
    char    *env_val;
    char    *env_name;
    int     len_name;
    char    *ret;

    len_name = 0;
    while (is_white_space(all->line[len_name]) && all->line[len_name])
        len_name++;
    env_name = (char *) malloc((len_name + 1) * sizeof(char));
    if (!env_name)
        error("handle_dollar: Malloc error\n", all);
    ft_strlcpy(env_name, all->line, len_name + 1);
    env_val = getenv(env_name);
    free(env_name);
    ret = (char *) malloc(sizeof(char) * (ft_strlen(env_val) + 1));
    if (!ret)
        error("hadnle_dollar: Malloc error\n", all);
    ft_strlcpy(ret, env_val, ft_strlen(env_val) + 1);
    all->line += len_name;
    return (ret);
}