/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:54:17 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/06 17:13:44 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef MINIHELL_H
# define MINIHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>


typedef struct msh
{
	int	argc;
	char	**env;
	char	**argv;
}		t_msh;

void	minishell(struct msh *msh, int argc, char **argv, char **env);

#endif
