/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ltoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 18:03:39 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/25 18:03:41 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	valid_lli(long long int nt, char c, int sign, int situation)
{
	if (situation == 1)
	{
		if (sign > 0 && ((nt > (LLONG_MAX - (c - 48)) / 10)
				|| (nt == (LLONG_MAX - (c - 48)) / 10
					&& c - 48 > LLONG_MAX % 10)))
			return (0);
	}
	if (situation == 2)
	{
		if (sign < 0 && ((nt > (LLONG_MIN + (c - 48)) / (-10))
				|| (nt == (LLONG_MIN + (c - 48)) / (-10)
					&& c - 48 > LLONG_MIN % 10 * (-1))))
			return (0);
	}
	return (1);
}

int	check_lli(char *argv)
{
	long long int	nt;
	int				i;
	int				sign;

	i = 0;
	nt = 0;
	sign = 1;
	if ((argv[i] == '-') || (argv[i] == '+'))
	{
		if (argv[i] == '-')
			sign = -sign;
		i++;
	}
	while (argv[i] >= '0' && argv[i] <= '9')
	{
		if (!valid_lli(nt, argv[i], sign, 1))
			return (0);
		if (!valid_lli(nt, argv[i], sign, 2))
			return (0);
		nt = nt * 10 + (argv[i] - 48);
		i++;
	}
	if (argv[i])
		return (0);
	return (1);
}

long long int	atolli(char *argv)
{
	long long int	nt;
	int				i;
	int				sign;

	i = 0;
	nt = 0;
	sign = 1;
	if ((argv[i] == '-') || (argv[i] == '+'))
	{
		if (argv[i] == '-')
			sign = -sign;
		i++;
	}
	while (argv[i] >= '0' && argv[i] <= '9')
	{
		nt = nt * 10 + (argv[i] - 48);
		i++;
	}

	return (nt *= sign);
}
