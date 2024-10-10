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
        t_env   *search;
        // int             i;

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
