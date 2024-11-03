/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:51:47 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:52:29 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_count_char(long num);

char	*ft_itoa(int n)
{
	int		num_char;
	char	*ret;
	int		sign;
	long	num;

	num = (long) n;
	sign = 0;
	if (num < 0)
	{
		sign = 1;
		num *= -1;
	}
	num_char = ft_count_char(num);
	ret = (char *) malloc(sizeof(char) * (num_char + 1 + sign));
	if (ret == NULL)
		return (NULL);
	ret[num_char + sign] = '\0';
	while (--num_char >= 0)
	{
		ret[num_char + sign] = (num % 10) + '0';
		num /= 10;
	}
	if (sign == 1)
		ret[0] = '-';
	return (ret);
}

static int	ft_count_char(long num)
{
	int	result;

	result = 0;
	while (num >= 10)
	{
		result++;
		num /= 10;
	}
	result++;
	return (result);
}
