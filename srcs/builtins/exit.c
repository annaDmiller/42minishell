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
/// @brief exit builtin
int	texit(t_msh *msh, t_cmd *cmd, t_args *argv)
{
	int	i;

	i = 0;
	if (!cmd->prev && !cmd->next) // if there is only one cmm it printf exit no matter what
		printf("exit\n");
	if (!argv) // if no argument then we break out of the main loop and msh->exit will stay as the last cmd exit code executed
		msh->have_to_exit = 1;
	else if (argv->next)
		printf("exit: too many arguments\n");
	else
	{
		while (argv->arg[i] && ft_isdigit(argv->arg[i])) // check if there is only digit characters
			i++;
		if (argv->arg[i]) // if argv->arg[i] exist it means we break out of the loop cause the caracter wasnt a digit
		{
			printf("error: numeric argument required\n");
			exit(2);
		}
		msh->exit = val_exit(ft_atoi(argv->arg)); // retrieve the good exit value 
		msh->have_to_exit = 1; // set msh->have_to_exit to 1 so we break out of the main loop
	}
	return (1);
}
