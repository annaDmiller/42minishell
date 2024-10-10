/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:03:26 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/10 14:03:29 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

// bash-5.1$ env -i unset PATH
// env: ‘unset’: No such file or directory
// bash-5.1$

void    unset(struct msh *msh, char *str)
{
        // ideally doubly linked list ill go previous but dk how to implement it
        t_env   *node;
        t_env   *tmp;
        // int             i;

        printf("\n\n\n\tje rentre dans unset\n\n");
        node = env_retrieve_var(msh->env, str); // pcque le nom de la variable est export nomdelavariable
        if (!node)
                return ;
        printf("l'id du node que je veux retirer = %d\n", node->id);
        tmp = msh->env;
        while (tmp && tmp->next->id != node->id) // je parcours ma liste avec tmp, lorsque le prochaine correspond a la var que je veux enlever je m'arrete
                tmp = tmp->next;
        if (!node->next) // if the var i want to unset is the last one in the list
        {
                free(node); // i just free it
                tmp->next = NULL; // and set ->next of the one before him to NULL
                return ;
        }
        tmp->next = node->next;
        printf("tmp->id = %d, node->next->id = %d", tmp->id, node->next->id);
        free(node->name);
        free(node->var);
        free(node);
        printf("\n\n\n\tje sors d'unset\n\n");
}
