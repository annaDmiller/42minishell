#include "../../includes/minishell.h"

static int  is_end_cmd(char car);

int is_empty_line(char *cmd_line)
{
    int ind;

    ind = 0;
    while (cmd_line[ind])
    {
        if (is_white_space(cmd_line[ind]))
            return (1);
        ind++;
    }
    return (0);
}

int  is_white_space(char car)
{
    if (car == ' ' || car == '\v' || car == '\t' || car == '\r'
        || car == '\f' || car == '\n')
        return (0);
    return (1);
}

int  find_end_cmd(char   *cmd_line)
{
    int ind;

    ind = 0;
    while (cmd_line[ind])
    {
        if (is_end_cmd(cmd_line[ind]))
            return (ind);
        ind++;
    }
    return (ind);
}

static int  is_end_cmd(char car)
{
    if (car == '|')
        return ((int) car);
    return (0);
}

int is_quote(char car)
{
    if (car == '\'' || car == '"')
        return (0);
    return (1);
}
