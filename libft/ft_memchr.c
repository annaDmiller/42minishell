/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:56:01 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:56:02 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(void *mem_src, int c, size_t n)
{
	unsigned char	*src;
	unsigned char	car;
	size_t			index;

	if (!mem_src)
		return (NULL);
	index = 0;
	car = (unsigned char) c;
	src = (unsigned char *) mem_src;
	while (index < n)
	{
		if (*(src + index) == car)
			return (mem_src + index);
		index++;
	}
	return (NULL);
}
