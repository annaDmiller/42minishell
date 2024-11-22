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

static	int	check_lli(char *argv)
{
	long long int	nt;
	int				i;
	int				sign;

	i = 0;
	nt = 0;
	sign = 1;
	if ((argv[i] == '-') || (argv[i] == '+'))
	{
		if (argv[i] == '-')
			sign = -sign;
		i++;
	}
	while (argv[i] >= '0' && argv[i] <= '9')
	{
		nt = nt * 10 + (argv[i] - 48);
		i++;
	}
	nt *= sign;
	if (nt > 9223372036854775807 || nt < -9223372036854775807)
		return (0);
	return (1);
}

static	int	atolli(char *argv)
{
	long long int	nt;
	int				i;
	int				sign;

	i = 0;
	nt = 0;
	sign = 1;
	if ((argv[i] == '-') || (argv[i] == '+'))
	{
		if (argv[i] == '-')
			sign = -sign;
		i++;
	}
	while (argv[i] >= '0' && argv[i] <= '9')
	{
		nt = nt * 10 + (argv[i] - 48);
		i++;
	}
	return (nt *= sign);
}

static	int	val_exit(long long int n)
{
	if (!n)
		return (0);
	n %= 256;
	if (n < 0)
		n = 256 + n;
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
	if (!(check_exit(msh, cmd, argv) && argv))
		return (1);
	while (argv->arg[i] && (ft_isdigit(argv->arg[i])
			|| (argv->arg[0] == '-')))
		i++;
	if (!check_lli(argv->arg) || argv->arg[i])
	{
		err_msg("error", argv->arg, "numeric argument required\n");
		msh->have_to_exit = 1;
		msh->exit = 2;
	}
	else if (argv && argv->next)
	{
		err_msg("exit", NULL, "too many arguments\n");
		msh->exit = 1;
	}
	else
	{
		msh->exit = val_exit(atolli(argv->arg));
		msh->have_to_exit = 1;
	}
	return (1);
}
