#include "../../includes/minishell.h"

t_cmd   *cmd_new(t_all *all)
{
    t_cmd   *new;

    new = (t_cmd *) malloc(sizeof(t_cmd));
    if (!new)
        error("cmd_new: Malloc error\n", all);
    new->next = NULL;
    new->prev = NULL;
    new->name = NULL;
    new->argv = NULL;
    new->opts = NULL;
    new->redir = NULL;
    return (new);
}