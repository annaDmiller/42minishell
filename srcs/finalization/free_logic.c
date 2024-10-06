#include "../../includes/minishell.h"

void    free_lst(t_cmd *lst_cmd)
{
    t_cmd   *temp;

    while (lst_cmd)
    {
        temp = lst_cmd->next;
        free(lst_cmd->name);
        ft_free_arr(lst_cmd->args);
        free(lst_cmd);
        lst_cmd = temp;
    }
    return ;
}