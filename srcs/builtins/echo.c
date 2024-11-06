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

/// @brief checking if str only contains one '-' and some 'n'
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

int	echo(t_args *argv)
{
	int	state;
	int	n;

	n = 1;
	state = 0;
	if (argv && argv->arg && valid(argv->arg)) // check the first argument if its a valid -n option
	{
		n = 0; // set n to 0 to dont print a \n at the end
		state = 1;
		argv = argv->next;
	}
	while (argv && argv->arg)
	{
		if (!(valid(argv->arg) && state == 1))
		{
			state = 0;
			putstr(argv->arg);
			if (argv->next) // if there is an argument next printf a space
				write(1, " ", 1);
		}
		argv = argv->next;
	}
	if (n)
		write(1, "\n", 1);
	return (1);
}
/// @brief simple putstr
void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}
