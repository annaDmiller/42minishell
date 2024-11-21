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

static int	valid(char *str);

int	echo(t_msh *msh, t_args *argv, int state, int n)
{
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
			if (!putstr(argv->arg))
			{
				msh->exit = 1;
				err_msg("echo", "write error", "No space left on device\n");
				return (1);
			}
			if (argv->next)
				write(1, " ", 1);
		}
		argv = argv->next;
	}
	if (n)
		write(1, "\n", 1);
	return (1);
}

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

int	putstr(char *str)
{
	while (*str)
		if (write(1, str++, 1) == -1)
			return (0);
	return (1);
}
