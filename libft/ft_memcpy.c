/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:56:34 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:56:35 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest_mem, const void *src_mem, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;
	size_t			index;

	if (!n)
		return (dest_mem);
	if (!dest_mem || !src_mem)
		return (NULL);
	dest = (unsigned char *) dest_mem;
	src = (unsigned char *) src_mem;
	index = -1;
	while (++index < n)
		dest[index] = src[index];
	return (dest_mem);
}
