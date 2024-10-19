/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:27 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:28 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	int	val_exit(int n)
{
	if (!n)
		return (0); // handle error
	if (n < 0)
	{
		while (n < -255)
			n /= 255;
		n = -n;
	}
	else
	{
		while (n > 255)
			n /= 255;
	}
//	comprendre la logique d'exit tt ce qu4il y a au dessus n'est pas bon	//	
	return (n);
}

void	texit(t_msh *msh, t_args *argv)
{
	printf("exit\n");
	if (!argv)
		msh->exit = 1;
	else if (argv->next)
		printf("exit: too many arguments\n");
	else
		msh->exit = val_exit(ft_atoi(argv->arg));
}
