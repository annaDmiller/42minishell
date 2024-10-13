/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 13:00:59 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 13:01:00 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*ret;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 && !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	ret = (char *) ft_calloc(sizeof(char), len_s1 + len_s2 + 1);
	if (ret == NULL)
		return (NULL);
	ft_strlcat(ret, s1, len_s1 + len_s2 + 1);
	ft_strlcat(ret, s2, len_s1 + len_s2 + 1);
	return (ret);
}
