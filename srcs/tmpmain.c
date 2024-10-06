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
#include "../include/minishell.h"

void	minishell(struct msh *msh, int argc, char **argv, char **env)
{
	(void)msh;
	(void)argc;
	(void)argv;
	(void)env;
}

void	out_redirect(char *str, char *file)
{
	int	i;
	int	tfd;
	DIR	*test;

	i = 0;
	
	// check if the file is a directyory by using opendir ? if it success then it is one 
	test = opendir(file);
	if (!(!test))
	{
		printf(": %s: Is a directory\n", file);
		exit (1); // bash --posix return 1 for that error and display "bash: file: Is a directory"
	}
	// if its not a directory we can create the file or trunc it if it already exists
	tfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);

}

int	main(int argc, char **argv, char **env)
{
//	struct msh	msh;

	(void)argc;
	(void)argv;
	(void)env;
	out_redirect("bonjour", "include");
//	minishell(&msh, argc, argv, env);
//	printf("%s\n", readline("minishell"));
	return (0);
}
