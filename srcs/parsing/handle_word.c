#include "../../includes/minishell.h"

char    *handle_word(t_all *all, t_cmd *cmd, int in_dollar)
{
    int ind;
    char    *str;

    ind = 0;
    while (all->line[ind] && is_white_space(all->line[ind]))
    {
        if (in_dollar && all->line[ind] == '$')
            break ;
        if (!is_quote(all->line[ind]) || !is_redir(all->line[ind]))
            break ;
        ind++;
    }
    str = (char *) malloc(sizeof(char) * (ind + 1));
    if (!str)
        error("handle_word: Malloc error\n", all);
    ft_strlcpy(str, all->line, ind + 1);
    all->line += ind;
    return (str);
}
