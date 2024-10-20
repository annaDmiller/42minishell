#include "../../includes/minishell.h"

void    exit_signal(t_all *all)
{
    free_all_struct(all, 1);
    exit(0);
}