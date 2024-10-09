/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:45:17 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/09 09:33:05 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "include/minishell.h"

int	tstrcmp(char *str, char *cmp)
{
	int	i;

	i = 0;
	while (str[i] || cmp[i])
	{
		if (str[i] != cmp[i])
			return (str[i] - cmp[i]);
		i++;
	}
	return (0);
}

///		faire un compteur du nombre de nom qui sont plus petit que lui
			// ainsi on aura sa position

void	export_alpha(struct msh *msh)
{
	t_env	*tmp;
	int		*order;
	char		**names;
	int		length;
	int		i;
	int		d;
	int		r;

	length = -1;
	tmp = msh->env;
	while (tmp)
	{
		++length;
		tmp = tmp->next;
	}
	names = malloc(sizeof(char *) * (length + 1));
	order = malloc(sizeof(int) * (length + 1));
	order[length] = 0;
	i = -1;
	tmp = msh->env;
	while (++i >= 0 && tmp)
	{
		names[i] = tstrdup(tmp->name);
		tmp = tmp->next;
	}
	i = -1;
	tmp = msh->env;
	while (++i < length)
	{
		r = -1;
		d = 0;
		while (++r < length)
			if (tstrcmp(tmp->name, names[r]) > 0)
				d++;
		order[d] = tmp->id;
		tmp = tmp->next;
	}
	i = -1;
	while (++i < length)
	{
		tmp = msh->env;
		while (tmp)
		{
			if (tmp->id == order[i])
				printf("%s=%s\n", tmp->name, tmp->var);
			tmp = tmp->next;
		}
	}
	i = -1;
	while (++i <= length)
		free(names[i]);
	free(names);
	free(order);
}		


