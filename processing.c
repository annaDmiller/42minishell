/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:21:58 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 08:22:00 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

void	everyinit(t_msh *msh, int argc, char **argv, char **envp)
{
	msh->pwd = malloc(sizeof(char) * 1000);
	getcwd(msh->pwd, 1000); // stock the pwd at the start, cd(directory);
//		handle if !getcwd
	if (envp[0])
		envinit(msh, envp, -1);
	else
		env_build(msh, -1);
	msh->argc = argc;
	msh->argv = argv;
	// printf("OJIWDWJOIQWDJIOQDWJIOQDWOJIQWD\n");
}
