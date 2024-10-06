/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:44:37 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/23 14:44:40 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include "libft.h"
# include <stdint.h>

int		ft_printf(const char *str, ...);
int		find_type(va_list *pars, char format);
int		print_string(va_list *pars);
int		print_num(va_list *pars);
int		print_point(va_list *pars);
int		print_uint(va_list *pars);
int		print_hex(uintptr_t num, char format);
void	find_lim(uintptr_t *lim, int *len_num, uintptr_t num);
#endif
