/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 01:10:43 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/21 01:10:46 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	cmd_check(t_all *all, t_msh *msh, t_cmd *cmd)
{
	DIR	*dir;

	if (!cmd || (cmd && !cmd->name) || (!cmd->has_to_be_executed))
		return (0);
	dir = opendir(cmd->name);
	if (dir)
	{
		closedir(dir);
		stderr_msg(NULL, cmd->name, "Is a directory\n");
		free_exit(all, msh, 1);
		exit(126);
		return (0);
	}
	return (1);
}

int	valid_export(t_msh *msh, char *n, int i)
{
	if (!n || (!((n[0] >= 65 && n[0] <= 90) || (n[0] >= 97
					&& n[0] <= 122)) && n[0] != '_'))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(n, 2);
		ft_putstr_fd("': not a valid indentifier\n", 2);
		msh->exit = 1;
		return (0);
	}
	while (n[++i] && n[i] != '=')
	{
		if (n[i] == '@' || n[i] == '~' || n[i] == '-' || n[i] == '.'
			|| n[i] == '{' || n[i] == '}' || n[i] == '*' || n[i] == '#'
			|| n[i] == '!' || n[i] == '+' )
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(n, 2);
			ft_putstr_fd("': not a valid indentifier\n", 2);
			msh->exit = 1;
			return (0);
		}
	}
	return (1);
}
