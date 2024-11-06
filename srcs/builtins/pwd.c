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

/// @brief printf the current pwd
int	pwd(t_msh *msh)
{
	if (msh->pwd)
		printf("%s\n", msh->pwd);
	else if (!msh->pwd) // it means we are in a deleted directory
		printf("error retrieving current directory: getcwd:\
cannot access parent directories: No such file or directory\n");
	return (1);
}
