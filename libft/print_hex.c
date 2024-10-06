/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:44:47 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/23 14:48:59 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_point(va_list *pars)
{
	void		*point;
	uintptr_t	str_p;

	point = va_arg(*pars, void *);
	str_p = (uintptr_t) point;
	if (str_p == 0)
		return (write(1, "(nil)", 5), 5);
	write(1, "0x", 2);
	return (print_hex(str_p, 'p') + 2);
}

int	print_hex(uintptr_t num, char format)
{
	uintptr_t	lim;
	int			len_num;
	char		*hex_lbase;

	find_lim(&lim, &len_num, num);
	hex_lbase = "0123456789abcdef";
	while (lim >= 1)
	{
		if (format == 'X')
			ft_putchar_fd(ft_toupper(hex_lbase[num / lim]), 1);
		else
			ft_putchar_fd(hex_lbase[num / lim], 1);
		num %= lim;
		lim /= 16;
	}
	return (len_num);
}

void	find_lim(uintptr_t *lim, int *len_num, uintptr_t num)
{
	int	count;

	*lim = 16;
	*len_num = 1;
	while (*lim - 1 < num)
	{
		(*lim) *= 16;
		(*len_num)++;
	}
	count = 1;
	*lim = 1;
	while (count++ < *len_num)
		*lim *= 16;
	return ;
}
