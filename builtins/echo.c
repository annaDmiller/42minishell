/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:20 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:21 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

// echo -nnnnnnnnnnn talan
// should work
// echo -nd talan
// should printf -nd talan

void	echo(t_msh *msh, t_cmd *cmd)
{
	// while ()
	// putstrfd(str, STDOUT_FILENO);
	// if (!cmd_line->next || !(tstrcmp(cmd_line->next, "-n") == 0)) // check if there is echo -n or not 
		// write(STDOUT_FILENO, "\n", 1);
	(void)msh;
	(void)cmd;
}
