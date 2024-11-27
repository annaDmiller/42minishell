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
	int		save;

	if (!str)
		return ;
	save = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s", str);
	dup2(save, STDOUT_FILENO);
	close(save);
}

void	err_msg(char *ft, char *arg, char *str)
{
	char	*msg;
	int		save;

	msg = tstrdup(ft);
	if (arg)
	{
		msg = tjoin(msg, ": ");
		msg = tjoin(msg, arg);
	}
	if (str)
	{
		msg = tjoin(msg, ": ");
		msg = tjoin(msg, str);
	}
	msg = tjoin(msg, "\n");
	save = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	printf("%s", msg);
	dup2(save, STDOUT_FILENO);
	close(save);
	free(msg);
}
