/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:40 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/05 17:49:41 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	pwd(t_msh *msh)
{
	if (msh->pwd)
		free(msh->pwd);
	msh->pwd = NULL;
	msh->pwd = getcwd(NULL, 0);
	if (msh->pwd)
	{
		printf("%s\n", msh->pwd);
		msh->exit = 0;
	}
	else
	{
		putstderr("pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		msh->exit = 1;
	}
	return (1);
}
