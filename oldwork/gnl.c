/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 23:23:49 by tespandj          #+#    #+#             */
/*   Updated: 2024/05/11 23:08:00 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

int	trouve(const char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*init_save(char *save)
{
	if (BUFFER_SIZE == 0)
		return (NULL);
	if (!save)
	{
		save = malloc(sizeof(char));
		if (!save)
			return (NULL);
		save[0] = '\0';
	}
	return (save);
}

char	*reset(char *buf, char **save, int i)
{
	if (i == 1)
		free(buf);
	else if (i == 2)
		free(*save);
	else if (i == 3)
	{
		free(buf);
		free(*save);
		*save = 0;
	}
	return (NULL);
}

static char	*fre(char *buf, char *str)
{
	free(buf);
	return (str);
}

char	*gnl(int fd)
{
	static char	*save;
	char		*buf;
	char		*str;
	ssize_t		rv;

	save = init_save(save);
	if (fd < 0 || BUFFER_SIZE <= 0 || !(save))
		return (0);
	buf = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buf)
		return (reset(buf, &save, 2));
	rv = 1;
	while (rv > 0 && !trouve(save))
	{
		rv = read(fd, buf, BUFFER_SIZE);
		if (rv < 0)
			return (reset(buf, &save, 3));
		buf[rv] = '\0';
		save = tjoin(save, buf);
		if (!save)
			return (NULL);
	}
	str = org(save);
	save = save_static(save, rv);
	return (fre(buf, str));
}
