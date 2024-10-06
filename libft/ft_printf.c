/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:44:29 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/23 14:44:31 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	pars;
	int		ind_str;
	int		len_pars;

	va_start(pars, str);
	ind_str = 0;
	len_pars = 0;
	while (str[ind_str])
	{
		if (str[ind_str] != '%')
		{
			ft_putchar_fd(str[ind_str], 1);
			len_pars++;
		}
		else
		{
			if (!str[ind_str + 1])
				break ;
			ind_str++;
			len_pars += find_type(&pars, str[ind_str]);
		}
		ind_str++;
	}
	va_end(pars);
	return (len_pars);
}

int	find_type(va_list *pars, char format)
{
	uintptr_t	hex_num;

	if (format == 'c')
		return (ft_putchar_fd((char) va_arg(*pars, int), 1), 1);
	if (format == 's')
		return (print_string(pars));
	if (format == 'i')
		return (print_num(pars));
	if (format == '%')
		return (ft_putchar_fd(format, 1), 1);
	if (format == 'd')
		return (print_num(pars));
	if (format == 'u')
		return (print_uint(pars));
	if (format == 'p')
		return (print_point(pars));
	if (format == 'X' || format == 'x')
	{
		hex_num = (uintptr_t) va_arg(*pars, unsigned int);
		return (print_hex(hex_num, format));
	}
	return (0);
}

int	print_string(va_list *pars)
{
	char	*str;

	str = va_arg(*pars, char *);
	if (str == NULL)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return ((int) ft_strlen(str));
}

int	print_num(va_list *pars)
{
	int		len_num;
	int		num;
	long	lim;
	long	long_num;

	num = va_arg(*pars, int);
	ft_putnbr_fd(num, 1);
	len_num = 1;
	lim = 10;
	long_num = (long) num;
	if (num < 0)
	{
		long_num *= -1;
		len_num ++;
	}
	while (lim <= long_num)
	{
		len_num++;
		lim *= 10;
	}
	return (len_num);
}

int	print_uint(va_list *pars)
{
	int				len_num;
	unsigned long	num;
	unsigned long	lim;

	num = (unsigned long) va_arg(*pars, unsigned int);
	len_num = 1;
	lim = 10;
	while (lim <= num)
	{
		len_num++;
		lim *= 10;
	}
	lim /= 10;
	while (lim >= 1)
	{
		ft_putchar_fd((num / lim) + '0', 1);
		num %= lim;
		lim /= 10;
	}
	return (len_num);
}
