/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adding_arguement.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:02 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:03 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

//function adds the str to the arguement list
void	add_arg(t_all *all, t_cmd *last, char **str)
{
	t_args	*new_arg;

	all->temp_for_free = *str;
	new_arg = arg_new(all);
	new_arg->arg = *str;
	all->temp_for_free = NULL;
	if (!last->argv)
		last->argv = new_arg;
	else
		arg_add_el_back(last, new_arg);
	return ;
}
