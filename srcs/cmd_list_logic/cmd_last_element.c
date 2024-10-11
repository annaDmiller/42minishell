#include "../../includes/minishell.h"

t_cmd   *cmd_last_el(t_all *all)
{
    t_cmd   *last;

    last = all->lst_cmd;
    while (last->next)
        last = last->next;
    return (last);
}