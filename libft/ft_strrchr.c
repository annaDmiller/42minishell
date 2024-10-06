/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:21:15 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/21 10:21:16 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *src, int c)
{
	size_t	index;
	char	car;

	if (!src)
		return (NULL);
	car = (char) c;
	index = ft_strlen(src);
	while (index != 0)
	{
		if (src[index] == car)
			return (src + index);
		index--;
	}
	if (src[index] == car)
		return (src + index);
	return (NULL);
}
