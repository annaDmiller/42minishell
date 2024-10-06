/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 10:20:44 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/21 10:20:45 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*ret;
	size_t	len_s;
	size_t	index;

	if (!s || !f)
		return (NULL);
	len_s = ft_strlen(s);
	ret = (char *) malloc (sizeof(char) * (len_s + 1));
	if (ret == NULL)
		return (NULL);
	index = 0;
	while (index < len_s)
	{
		ret[index] = (*f)(index, s[index]);
		index++;
	}
	ret[index] = '\0';
	return (ret);
}
