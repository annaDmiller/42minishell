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

static	int	check_slash(char *str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		if (str[i] == '/')
			return (1);
	return (0);
}

int	cmd_check(t_all *all, t_msh *msh, t_cmd *cmd)
{
	if (!tstrcmp(cmd->name, "."))
	{
		err_msg("bash", ".", "filename argument required");
		err_msg(".", "usage", ". filename [arguments]");
		free_exit(all, msh, 1);
		exit(2);
	}
	else if (!tstrcmp(cmd->name, "..") || (!tstrcmp(cmd->name, "")))
		return (0);
	if (check_slash(cmd->name))
	{
		if (access(cmd->name, F_OK))
		{
			msh->exit = 127;
			err_msg(cmd->name, "No such file or directory", NULL);
			return (0);
		}
		if (access(cmd->name, R_OK) == -1  || access(cmd->name, X_OK) == -1)
		{
			msh->exit = 126;
			return (0);
		}
		return (1);
	}
	msh->data->path = fpath(msh->env, cmd->name, -1);
	if (msh->data->path)
	{
		free(msh->data->path);
		return (1);
	}
	msh->exit = 127;
	err_msg(cmd->name, "command not found", NULL);
	return (0);
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
