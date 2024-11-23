/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlist.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 19:25:25 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 19:25:27 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	l_envsize(t_env *env)
{
	t_env	*tmp;
	int		l;

	l = 0;
	tmp = env;
	while (tmp && ++l > 0)
		tmp = tmp->next;
	return (l);
}

int	l_argsize(t_args *argv)
{
	t_args	*tmp;
	int		l;

	l = 0;
	tmp = argv;
	while (tmp && ++l > 0)
		tmp = tmp->next;
	return (l);
}

int	curr_dir(void)
{
	DIR	*dir;

	dir = opendir(".");
	if (!dir)
		return (0);
	closedir(dir);
	return (1);
}

void	putstderr(char *str)
{
	while (*str)
		write(2, str++, 1);
}

void	err_msg(char *ft, char *arg, char *str)
{
	if (ft)
	{
		putstderr(ft);
		write(2, ": ", 2);
	}
	if (arg)
	{
		putstderr(arg);
		write(2, ": ", 2);
	}
	putstderr(str);
}
