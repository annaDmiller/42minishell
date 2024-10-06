/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:43:53 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/21 11:43:54 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*realloc_line(char *line, char **buff)
{
	size_t	len_line;
	char	*ret_line;
	size_t	check_ind;
	size_t	len_new_line;

	len_line = ft_strlen(line);
	check_ind = find_nl(*buff);
	if (ft_strlen(*buff) == check_ind)
		len_new_line = len_line + check_ind;
	else
		len_new_line = len_line + check_ind + 1;
	ret_line = (char *) malloc((len_new_line + 1) * sizeof(char));
	if (!ret_line)
		return (NULL);
	ret_line[0] = '\0';
	ft_strlcat(ret_line, line, len_new_line + 1);
	ft_strlcat(ret_line, *buff, len_new_line + 1);
	free(line);
	return (ret_line);
}

size_t	find_nl(char *str)
{
	size_t	ind;

	ind = 0;
	while (str[ind])
	{
		if (str[ind] == '\n')
			return (ind);
		ind++;
	}
	return (ind);
}
