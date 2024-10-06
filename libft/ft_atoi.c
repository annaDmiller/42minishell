/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:49:33 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:49:44 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	number;
	int	ind;
	int	sign;

	if (!nptr)
		return (0);
	ind = 0;
	number = 0;
	sign = 1;
	while (nptr[ind] == ' ' || (nptr[ind] >= 9 && nptr[ind] <= 13))
		ind++;
	if (nptr[ind] == '-' || nptr[ind] == '+')
		if (nptr[ind++] == '-')
			sign *= -1;
	while (ft_isdigit(nptr[ind]))
	{
		number = 10 * number + nptr[ind] - 48;
		ind++;
	}
	return (sign * number);
}
