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

void	putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}


void	everyinit(t_msh *msh, int argc, char **argv, char **envp)
{
	msh->pwd= NULL;
	msh->pwd = getcwd(NULL, 0); // stock the pwd at the start, cd(directory);
//		handle if !getcwd
	if (envp && envp[0])
		envinit(msh, envp, -1);
	else
	{
		env_build(msh, -1);
		// putstr(msh->pwd);
		// putstr("\n");
		// putstr("AHLEMAHLEMAHLEMAHLEMAHLEMAHLEMAHLEMAHLEM\n");
		// printf("AHLEMAHLEMAHLEMAHLEMAHLEMAHLEMAHLEMAHLEM\n\n\n");
		// printf("\t\t%s\n", msh->pwd);
	}
	msh->argc = argc;
	msh->argv = argv;
	// printf("OJIWDWJOIQWDJIOQDWJIOQDWOJIQWD\n");
}
