/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 22:13:37 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/06 22:13:40 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	int	val_exit(int n)
{
	if (!n)
		return (0);
	n %= 256;
	if (n < 0)
		n = -n;
	return (n);
}

int	texit(t_msh *msh, t_cmd *cmd, t_args *argv)
{
	int	i;

	i = 0;
	if (!cmd->prev && !cmd->next)
		printf("exit\n");
	if (!argv)
	{
		// msh->exit = 0;
		msh->have_to_exit = 1;
	}
	else if (argv)
	{
		while (argv->arg[i] && ft_isdigit(argv->arg[i]))
			i++;
		if (argv->arg[i])
		{
			fprintf(stderr, "error: %s:numeric argument required\n", argv->arg);
			msh->exit = 2;
		}
		else
			msh->exit = val_exit(ft_atoi(argv->arg));
		msh->have_to_exit = 1;

	}
	if (argv && argv->next)
	{
		fprintf(stderr, "exit: too many arguments\n");
		msh->have_to_exit = 0;
		msh->exit = 1;
	}
	return (1);
}
