/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:43:25 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/06 16:55:07 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buff;
	char		*line;
	static char	*tails[1024];
	int			check;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buff = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	check = form_line(&line, &(tails[fd]), &buff, fd);
	free(buff);
	if (check == -1)
		return (NULL);
	return (line);
}

int	form_line(char **line, char **tail, char **buff, int fd)
{
	ssize_t	byte;
	int		check;

	if (*tail != NULL)
	{
		check = check_tail(tail, line);
		if (check == -1)
			return (check);
		if (check == 1)
			return (update_tail(tail, line));
	}
	byte = read(fd, *buff, BUFFER_SIZE);
	while (byte > 0)
	{
		(*buff)[byte] = '\0';
		*line = realloc_line(*line, buff);
		if (!(*line))
			return (-1);
		check = create_tail(buff, tail);
		if (check)
			return (check);
		byte = read(fd, *buff, BUFFER_SIZE);
	}
	return (0);
}

int	check_tail(char **tail, char **line)
{
	size_t	ind_nl;
	size_t	len_tail;

	ind_nl = find_nl(*tail);
	len_tail = ft_strlen(*tail);
	if (ind_nl == len_tail)
	{
		*line = (char *) malloc((len_tail + 1) * sizeof(char));
		if (!(*line))
			return (free(*tail), -1);
		(*line)[0] = '\0';
		ft_strlcat(*line, *tail, len_tail + 1);
		return (free(*tail), *tail = NULL, 0);
	}
	*line = (char *) malloc((ind_nl + 2) * sizeof(char));
	if (!(*line))
		return (free(*tail), -1);
	(*line)[0] = '\0';
	ft_strlcat(*line, *tail, ind_nl + 2);
	return (1);
}

int	update_tail(char **tail, char **line)
{
	size_t	ind_nl;
	size_t	ind;
	char	*new_tail;

	ind_nl = find_nl(*tail);
	if (!((*tail)[ind_nl + 1]))
		return (free(*tail), *tail = NULL, 0);
	ind = 0;
	new_tail = (char *) malloc((ft_strlen(*tail) - ind_nl + 1) * sizeof(char));
	if (!new_tail)
		return (free(*tail), free(*line), -1);
	ind_nl++;
	while ((*tail)[ind + ind_nl])
	{
		new_tail[ind] = (*tail)[ind + ind_nl];
		ind++;
	}
	new_tail[ind] = '\0';
	free(*tail);
	*tail = new_tail;
	return (1);
}

int	create_tail(char **buff, char **tail)
{
	size_t	check_ind;
	size_t	ind;
	size_t	len_buff;

	check_ind = find_nl(*buff);
	len_buff = ft_strlen(*buff);
	if (check_ind == len_buff)
		return (0);
	if (check_ind == len_buff - 1)
		return (1);
	*tail = (char *) malloc((len_buff - check_ind) * sizeof(char));
	if (!(*tail))
		return (-1);
	ind = 0;
	while ((*buff)[check_ind + ind + 1])
	{
		(*tail)[ind] = (*buff)[check_ind + ind + 1];
		ind++;
	}
	(*tail)[ind] = '\0';
	return (1);
}
