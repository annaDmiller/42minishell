/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlib.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:22:11 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/23 02:42:34 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"
#include "dirent.h"

char	*tstrdup(char *src)
{
	int		i;
	char	*dest;

	i = -1;
	if (!src)
		return (NULL);
	dest = malloc(sizeof(char) * (tstrlen(src) + 1));
	if (!dest)
		return (NULL);
	while (src[++i] != '\0')
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

char	*tjoin(char *str, char *add)
{
	char	*tzy;
	int		i;
	int		t;

	i = -1;
	t = -1;
	tzy = malloc(sizeof(char) * (tstrlen(add) + tstrlen(str) + 1));
	if (!tzy)
		return (NULL);
	while (str && str[++i] != '\0')
		tzy[i] = str[i];
	while (add && add[++t] != '\0')
		tzy[i + t] = add[t];
	tzy[i + t] = '\0';
	free(str);
	return (tzy);
}

int	tstrlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	tstrcmp(char *str, char *cmp)
{
	int	i;

	i = -1;
	while (str[++i] || cmp[i])
		if (str[i] != cmp[i])
			return (str[i] - cmp[i]);
	return (0);
}

int	dir_check(char *file)
{
	struct dirent	*ye;
	DIR				*dir;

	if (!file)
		return (0);
	dir = opendir(file);
	if (dir)
	{
		closedir(dir);
		return (1);
	}
	dir = opendir(".");
	ye = readdir(dir);
	while (ye)
	{
		if (!tstrcmp(ye->d_name, file) && ye->d_type == DT_REG)
		{
			closedir(dir);
			return (0);
		}
		ye = readdir(dir);
	}
	closedir(dir);
	return (2);
}
