/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:00:41 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 13:00:42 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*ret;
	size_t	len_src;

	if (!src)
		return (NULL);
	len_src = ft_strlen(src);
	ret = (char *) malloc(sizeof(char) * (len_src + 1));
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, src, len_src + 1);
	return (ret);
}
