/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tlib.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:22:11 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 21:22:14 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	tstrcmp(char *str, char *cmp)
{
	int	i;

	i = -1;
	while (str[++i] || cmp[i])
		if (str[i] != cmp[i])
			return (str[i] - cmp[i]);
	return (0);
}

int	tstrlen(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*tstrdup(char *src)
{
	int		i;
	char	*dest;

	if (!src)
		return (NULL);
	dest = malloc(sizeof(char) * (tstrlen(src) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*tjoin(char *str, char *add)
{
	char	*tzy;
	int		i;
	int		t;

	i = -1;
	t = -1;
	tzy = malloc(sizeof(char) * (tstrlen(add) + tstrlen(str) + 1));
	if (!tzy)
		return (NULL);
	while (str[++i] != '\0')
		tzy[i] = str[i];
	while (add[++t] != '\0')
		tzy[i + t] = add[t];
	tzy[i + t] = '\0';
	free(str);
	return (tzy);
}
