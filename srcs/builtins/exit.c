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

static int	check_chr(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!ft_isdigit(str[i]))
		{
			ft_putstr_fd("error: numeric argument required", 2);
			return (2); 
		}
	}
	return (1);
}
static	int	val_exit(int n)
{
	if (!n)
		return (0); // handle error
	n %= 256;
	if (n < 0)
		n = -n;
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
	{
		if (check_chr(argv->arg) == 2)
			exit(2);
		msh->exit = val_exit(ft_atoi(argv->arg));
	}
}
