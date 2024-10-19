/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 20:19:11 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/08 20:19:13 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	redirin(char *str, char *file);

void	redirout(char *str, char *file)
{
//	int	tfd;
	
	(void)str;
	(void)file;
	// check if the file is a directyory by using opendir ? if it success then it is one 
	// if its not a directory we can create the file or trunc it if it already exists
//	tfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);

}

void	append(char *str, char *file);

void	heredoc(char *str);


