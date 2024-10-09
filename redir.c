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
#include "include/minishell.h"

void	redirin(char *str, char *file);

void	redirout(char *str, char *file)
{
//	int	tfd;
	DIR	*test;
	
	(void)str;
	// check if the file is a directyory by using opendir ? if it success then it is one 
	test = opendir(file);
	if (test)
	{
		printf(": %s: Is a directory\n", file);
		exit (1); // bash --posix return 1 for that error and display "bash: file: Is a directory"
	}
	printf("Ain't no directory there son\n");
	// if its not a directory we can create the file or trunc it if it already exists
//	tfd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);

}

void	append(char *str, char *file);

void	heredoc(char *str);


char	*fpath_tt(char *cmd, int i)
{
	char	**str;
	char	*path;

	if (!access(cmd, F_OK | X_OK))	// try to acces the cmd right now, maybe its it absolute path
		return (cmd);
	path = NULL;
	str = split(getenv("PATH"), ':');  // getenv and split it with ":" to try to build every possible path
	if (!str)
		return (0);
	while (str[++i])
	{
		str[i] = tjoin(tjoin(str[i], "/"), cmd);  // building paths
		if (!access(str[i], F_OK | X_OK)) // check if the file of the path exist and if its executable
			break ;		// if yes we break the loop
	}
	if (str[i])	// if we didnt find any path str[i] == NULL it wont check the condition
		path = tstrdup(str[i]);
	fsplit(str);
	return (path);
}
