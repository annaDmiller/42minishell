/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:25:25 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 19:25:27 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

int	l_envsize(t_env *env)
{
	t_env	*tmp;
	int	l;

	l = 0;
	tmp = env;
	while (tmp && ++l > 0)
		tmp = tmp->next;
	return (l);
}

int	l_argsize(t_args *argv)
{
	t_args	*tmp;
	int	l;

	l = 0;
	tmp = argv;
	while (tmp && ++l > 0)
		tmp = tmp->next;
	return (l);

}
