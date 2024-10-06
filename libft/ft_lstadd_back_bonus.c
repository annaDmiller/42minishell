/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:52:46 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:52:47 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*cur_el;

	if (lst)
	{
		cur_el = *lst;
		if (cur_el)
		{
			while (cur_el->next)
				cur_el = cur_el->next;
			cur_el->next = new;
		}
		else
			*lst = new;
	}
	return ;
}
