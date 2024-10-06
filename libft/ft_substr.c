/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:31:15 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/21 10:31:16 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ret;
	size_t	len_s;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	if (start > len_s)
		return (ft_strdup(""));
	if (start + len > len_s)
		len_s = len_s - start + 1;
	else
		len_s = len + 1;
	ret = (char *) malloc(sizeof(char) * len_s);
	if (!ret)
		return (NULL);
	s += start;
	ft_strlcpy(ret, s, len_s);
	return (ret);
}
