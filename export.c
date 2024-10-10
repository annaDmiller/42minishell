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


void	export(struct msh *msh)
{
	// if (no option for export)
		// export_no_opt(msh);
	// if (def a variable)
		// export_def(msh, str);
	(void)msh;
}

void	export_def(struct msh *msh, char *str)
{
	t_env	*head;
	t_env	*new;
	
	head = msh->env;
	while (msh->env->next)
		msh->env = msh->env->next;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ; // handle error
	new->name = env_varname(str);
 	new->var = env_var(str);
	new->id = -2;
	new->next = NULL;
	msh->env->next = new;
	msh->env = head;
}

static int	tstrcmp(char *str, char *cmp)
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

void	export_no_opt(struct msh *msh)
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
				printf("export %s=\"%s\"\n", tmp->name, tmp->var);
			tmp = tmp->next;
		}
	}
	i = -1;
	while (++i <= length)
		free(names[i]);
	free(names);
	free(order);
}
