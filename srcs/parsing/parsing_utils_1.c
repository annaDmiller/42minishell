#include "../../includes/minishell.h"

int count_len_bfr_ws(char *line)
{
    int ind;

    ind = 0;
    while (line[ind])
    {
        if (!is_white_space(line[ind]))
            return (ind);
        ind++;
    }
    return (ind);
}

int is_redir(char car)
{
    if (car == '>' || car == '<' || car == '|')
        return (0);
    return (1);
}