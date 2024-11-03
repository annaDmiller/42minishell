/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:40 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:41 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	pwd(t_msh *msh)
{
	if (msh->pwd)
		printf("%s\n", msh->pwd);
	else
		printf("error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
	return (1);
}
