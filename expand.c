/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:21:42 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 08:21:45 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

// idealement en argument un pointeur sur le noeud $USER dans la ligne de commande
char	*expand(struct msh *msh, char *str)
{
	return (env_retrieve_var(msh->env, str)->var);
}
