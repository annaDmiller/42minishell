/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:20 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:21 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static int	valid(char *str)
{
	int	i;

	i = 0;
	if (!(str[0] == '-'))
		return (0);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (0);
	}
	return (22);
}

int	echo(t_msh *msh, t_args *argv)
{
	int	state;
	int	n;

	n = 1;
	state = 0;
	if (argv && argv->arg && valid(argv->arg))
	{
		n = 0;
		state = 1;
		argv = argv->next;
	}
	while (argv && argv->arg)
	{
		if (!(valid(argv->arg) && state == 1))
		{
			state = 0;
			putstr(argv->arg);
			if (argv->next)
				write(1, " ", 1);
		}
		argv = argv->next;
	}
	if (n)
		write(1, "\n", 1);
	(void)msh;
	return (1);
}
