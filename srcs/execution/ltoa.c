/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 03:10:40 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/25 03:10:43 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static int	nnumber(long long int number)
{
	int	c;

	c = 0;
	if (number < 0)
	{
		number = -number;
		c++;
	}
	while (number != 0)
	{
		number /= 10;
		c++;
	}
	return (c);
}

char	*ltoa(long long int in)
{
	int	length;
	char	*str;


	length = nnumber(in);
	str = malloc(sizeof(char) * (length + 1));
	if (!str)
		return (NULL);
	if (in == 0)
		str[0] = '0';
	str[length] = '\0';
	while (in != 0)
	{
		str[length] = llabs(in % 10);
		length--;
		in /= 10;
	}
	if (length == 0)
		str[0] = '-';
	return (str);
}
