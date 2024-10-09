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

void    everyinit(struct msh *msh, int argc, char **argv, char **envp)
{
	envinit(msh, envp, -1);
	msh->pwd = malloc(sizeof(char) * 1000);
	getcwd(msh->pwd, 1000); // stock the pwd at the start, then we'll change it according to every directory change we do
//		 handle if !getcwd
	msh->argc = argc;
	msh->argv = argv;
}
