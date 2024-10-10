#include "include/minishell.h"

void    unset(struct msh *msh, char *str)
{
        // ideally doubly linked list ill go previous but dk how to implement it
        t_env   *node;
        t_env   *tmp;
        t_env   *search;
        int             i;

        node = env_retrieve_var(msh->env, str);
        if (!node)
                return ;
        if (!node->next)
        {
                free(node);
                node = NULL;
                return ;
        }
        tmp = node->next;
        search = msh->env;
        while (search->next->id != node->id)
                search = search->next;
        search->next = tmp;
        
}