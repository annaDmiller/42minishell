/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:00:33 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 13:00:34 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(char	*src, int c)
{
	int		index;
	char	car;

	if (!src)
		return (NULL);
	car = (char) c;
	if (car == '\0')
		return (src + ft_strlen(src));
	index = -1;
	while (src[++index])
	{
		if (src[index] == car)
			return (src + index);
	}
	return (NULL);
}
