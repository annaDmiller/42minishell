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

//	leaks sur env_varname(str) && env_var(str) ! le noeud cree n'est pas relie correctement a la list ?

void	export_def(struct msh *msh, char *str)
{
	char	*name;
	t_env	*head;
	t_env	*new;
	t_env	*var;
	int	tmpid;

	if (!str)
		return ;	
	name = setup_name(str);
	var = env_retrieve_var(msh->env, name);
	if (var) // si la variable existe deja on modifie seulement son contenu
	{
		free(var->var);
		var->var = env_var(str);
		return (freestr(name));
	}
	if (!((str[0] >= 65 && str[0] <= 90) || (str[0] >= 97 && str[0] <= 122)) && str[0] != '_')
	{
		printf("export: `%s': not a valid indentifier\n", str);
		return (freestr(name));
	}
	head = msh->env;
	tmpid = msh->env->id;
	while (msh->env->next)
	{
		msh->env = msh->env->next;
		tmpid = msh->env->id;
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (freestr(name)); // handle error
	new->name = env_varname(str);
 	new->var = env_var(str);
	new->id = tmpid + 1;
	new->next = NULL;
	msh->env->next = new;
	msh->env = head;
}

int	tstrcmp(char *str, char *cmp)
{
	int	i;

	i = -1;
	while (str[++i] || cmp[i])
		if (str[i] != cmp[i])
			return (str[i] - cmp[i]);
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
