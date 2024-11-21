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

static	int	check_exit(t_msh *msh, t_cmd *cmd, t_args *argv)
{
	if (!cmd->prev && !cmd->next)
		printf("exit\n");
	if (!argv)
	{
		msh->have_to_exit = 1;
		return (0);
	}
	return (1);
}

int	texit(t_msh *msh, t_cmd *cmd, t_args *argv)
{
	int	i;

	i = 0;
	if (check_exit(msh, cmd, argv) && argv)
	{
		while (argv->arg[i] && ft_isdigit(argv->arg[i]))
			i++;
		if (argv->arg[i])
		{
			stderr_msg("error", argv->arg, "numeric argument required\n");
			msh->exit = 2;
		}
		else if (argv && argv->next)
		{
			stderr_msg("exit", NULL, "too many arguments\n");
			msh->exit = 1;
		}
		else
		{
			msh->exit = val_exit(ft_atoi(argv->arg));
			msh->have_to_exit = 1;
		}
	}
	return (1);
}
