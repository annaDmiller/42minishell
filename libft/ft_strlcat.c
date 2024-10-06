/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:01:07 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 13:01:09 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t sz)
{
	size_t	index;
	size_t	len_dest;
	size_t	len_src;

	if (dest && src)
	{
		len_dest = ft_strlen(dest);
		len_src = ft_strlen(src);
		if (sz <= len_dest)
			return (len_src + sz);
		index = 0;
		while (src[index] && len_dest + index < sz - 1)
		{
			dest[len_dest + index] = src[index];
			index++;
		}
		dest[len_dest + index] = '\0';
		return (len_dest + len_src);
	}
	return (0);
}
