/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:32:24 by tespandj          #+#    #+#             */
/*   Updated: 2024/05/11 23:08:10 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

static int	g_value(char *str, int a)
{
	int	i;

	i = 0;
	if (a == 1)
	{
		while (str[i] && str[i] != '\n')
			i++;
		if (str[i] == '\n')
			i++;
		if (!str[i])
			return (-1);
		return (i);
	}
	else
	{
		if (!str)
			return (0);
		while (str[i])
			i++;
		return (i);
	}
}

char	*save_static(char *str, int rv)
{
	char	*new_static;
	int		i;
	int		j;

	j = 0;
	i = g_value(str, 1);
	if (rv == 0 || str[0] == 0 || i == -1)
	{
		free(str);
		return (NULL);
	}
	new_static = malloc(sizeof(char) * ((g_value(str, 22) - i) + 1));
	if (!new_static)
	{
		free(str);
		return (NULL);
	}
	while (str[i])
		new_static[j++] = str[i++];
	new_static[j] = '\0';
	free(str);
	return (new_static);
}

char	*org(char *str)
{
	char	*res;
	int		i;

	i = 0;
	if (!str || !str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	res = malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		res[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		res[i++] = '\n';
	res[i] = '\0';
	return (res);
}
