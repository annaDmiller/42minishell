/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temporary_parsing.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 18:01:52 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/13 18:02:05 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

/// @brief parse argv given after ./minishell and parse it into a linked list to test before final version of parsing
void	parse_cmd_line(t_msh *msh, char **argv)
{
	t_args	*tmp;
	int		i;

	i = 0;
	msh->l_args = NULL;
	while (argv[++i])
	{
		if (msh->l_args == NULL)
		{
			msh->l_args = (t_args *)malloc(sizeof(t_args));
			if (msh->l_args == NULL)
				return ; // error malloc
			tmp = msh->l_args;
		}
		else
		{
			tmp->next = (t_args *)malloc(sizeof(t_args));
			if (tmp->next == NULL)
				return ; // error malloc
			tmp = tmp->next;
		}
		tmp->arg = argv[i];
		tmp->next = NULL;
		// printf("\t\t\t// // %d\n", i);
	}
}
