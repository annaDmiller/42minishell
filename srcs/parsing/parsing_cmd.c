#include "../../includes/minishell.h"

void    parse_cmd(t_all *all)
{
    int end_cmd;
    int ind;
    t_cmd   *last;
    int     len_word;

    ind = 0;
    end_cmd = find_end_cmd(all->line);
    last = cmd_last_el(all);
    ind += add_cmd_name(all, last);
    while (ind <= end_cmd)
    {
        if (is_white_space(all->line[ind]))
        {
            if (!is_redir(all->line[ind]))
                ind = handle_redir(all, ind, last);
            else if (!is_quote(all->line[ind]))
                ind = handle_quotes(all, ind, last, "arg");
            else if (all->line[ind] == '$')
                ind = handle_dollar(all, ind, last);
            else
                ind = handle_word_arg(all, ind, last);  
        }
        else
            ind++;
    }
    all->line += ind;
    return ;
}

int add_cmd_name(t_all *all, t_cmd *last)
{
    int     len_name;
    char    *cmd_name;

    len_name = count_len_bfr_ws(all->line);
    cmd_name = (char *) malloc((len_name + 1) * sizeof(char));
    if (!cmd_name)
        error("add_cmd_name: Malloc error\n", all);
    ft_strlcpy(cmd_name, all->line, len_name + 1);
    last->name = cmd_name;
    return (len_name + 1);
}