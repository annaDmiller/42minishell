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
		msh->have_to_exit = 1;
	else if (argv->next)
		printf("exit: too many arguments\n");
	else
	{
		while (argv->arg[i] && ft_isdigit(argv->arg[i]))
			i++;
		if (argv->arg[i])
		{
			printf("error: numeric argument required\n");
			exit(2);
		}
		msh->exit = val_exit(ft_atoi(argv->arg));
		msh->have_to_exit = 1;
	}
	return (1);
}
