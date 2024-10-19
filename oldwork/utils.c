/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 21:59:04 by tespandj          #+#    #+#             */
/*   Updated: 2024/09/12 16:03:38 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/pipex.h"

char	*fpath(char **env, char *cmd, int i)
{
	char	**str;
	char	*path;

	if (!access(cmd, F_OK | X_OK))
		return (cmd);
	path = NULL;
	while (env[++i])
		if (env[i][4] && env[i][0] == 'P' && env[i][1] == 'A'
			&& env[i][2] == 'T' && env[i][3] == 'H' && env[i][4] == '=')
			break ;
	str = split(env[i], ':');
	if (!str)
		return (0);
	str[0] = first_path(str[0]);
	i = -1;
	while (str[++i])
		str[i] = tjoin(tjoin(str[i], "/"), cmd);
	i = -1;
	while (str[++i])
		if (!access(str[i], F_OK | X_OK))
			break ;
	if (str[i])
		path = tstrdup(str[i]);
	fsplit(str);
	return (path);
}

char	*first_path(char *str)
{
	char	*path;
	int		i;
	int		r;

	r = 0;
	i = 5;
	path = malloc(sizeof(char) * tstrlen(str) - 4);
	if (!path)
		return (NULL);
	while (str[i])
	{
		path[r] = str[i];
		i++;
		r++;
	}
	free(str);
	path[r] = '\0';
	return (path);
}
