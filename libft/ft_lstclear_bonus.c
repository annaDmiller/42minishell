/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 11:53:04 by amelniko          #+#    #+#             */
/*   Updated: 2024/06/20 11:53:05 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cur_el;

	if (lst && (*del))
	{
		if (*lst)
		{
			cur_el = *lst;
			if (cur_el->next)
				ft_lstclear(&(cur_el->next), (*del));
			(*del)(cur_el->content);
		}
		free(*lst);
		*lst = NULL;
	}
	return ;
}
