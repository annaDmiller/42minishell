/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:50:17 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:50:20 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t sztype, size_t n)
{
	void	*ret;

	if (!sztype || !n)
		return (NULL);
	if (sztype > UINT_MAX / n)
		return (NULL);
	ret = malloc(sztype * n);
	if (!ret)
		return (NULL);
	ft_bzero(ret, sztype * n);
	return (ret);
}
