/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmpmain.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/06 17:40:23 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

// void	minishell(struct msh *msh, int argc, char **argv, char **env)
// {
// 	(void)msh;
// 	(void)argc;
// 	(void)argv;
// 	(void)env;
// }

int	main(void)
{
	printf("%s\n", fpath_tt("ls", -1));
	return (0);
}
