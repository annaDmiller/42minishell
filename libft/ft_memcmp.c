/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:56:25 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:56:26 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *mem1, const void *mem2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			index;

	if (!mem1 || !mem2)
		return (0);
	index = 0;
	s1 = (unsigned char *) mem1;
	s2 = (unsigned char *) mem2;
	while (index < n)
	{
		if (s1[index] != s2[index])
			return (s1[index] - s2[index]);
		index++;
	}
	return (0);
}
