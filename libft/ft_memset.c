/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:56:59 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:57:01 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *mem, int let, size_t n)
{
	char			*str;
	unsigned char	car;

	if (!mem)
		return (NULL);
	str = (char *) mem;
	car = (unsigned char) let;
	while (n--)
		str[n] = car;
	return (mem);
}
