/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:36 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:37 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/minishell.h"

void	export(t_msh *msh, t_args *argv)
{
	t_env	*var;
	char		*n;

	if (!argv)
		export_no_opt(msh);
	while (argv)
	{
		n = setup_name(argv->arg);
		if (!((n[0] >= 65 && n[0] <= 90) || (n[0] >= 97 && n[0] <= 122)) && n[0] != '_')
			printf("export: `%s': not a valid indentifier\n", argv->arg);
		else
		{
			var = env_retrieve_var(msh->env, n);
			if (var) // si la variable existe deja on modifie seulement son contenu
			{
				free(var->var);
				var->var = env_var(argv->arg);
			}
			else
				export_def(msh, argv);
		}
		argv = argv->next;
		free(n);
	}
}

//	leaks sur env_varname(str) && env_var(str) ! le noeud cree n'est pas relie correctement a la list ?

/// @brief leaks sur env_varname(str) && env_var(str)
/// le noeud cree n'est pas relie correctement a la list ?
/// Reamenager avec t_args *argv en argument
/// if not a valid indentifier we still need to create the node 
void	export_def(t_msh *msh, t_args *argv)
{
	t_env	*new;
	t_env	*head;
	int		index;
	
	head = msh->env;
	index = msh->env->id;
	while (msh->env->next)
	{
		msh->env = msh->env->next;
		index = msh->env->id;
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ; // handle error
	msh->env->next = new;
	new->id = index + 1;
	new->name = env_varname(argv->arg);
	new->var = env_var(argv->arg);
	new->next = NULL;
	msh->env = head;
}

void	export_no_opt(t_msh *msh)
{
	t_env	*tmp;
	int		*order;
	char		**names;
	int		length;
	int		i;
	int		d;
	int		r;

	length = lsize(msh->env) - 1; // -1 pour commencer a 0 dans les tab[i]
	names = malloc(sizeof(char *) * (length + 1));
	order = malloc(sizeof(int) * (length + 1));
	i = -1;
	tmp = msh->env;
	while (tmp)
	{
		names[++i] = tstrdup(tmp->name);
		tmp = tmp->next;
	}
	i = -1;
	tmp = msh->env;
	while (++i <= length)
	{
		d = 0;
		r = -1;
		while (++r <= length)
			if (tstrcmp(tmp->name, names[r]) > 0)
				d++;
		order[d] = tmp->id;
		tmp = tmp->next;
	}
	i = -1;
	while (++i <= length)
	{
		tmp = msh->env;
		while (tmp)
		{
			if (tmp->id == order[i])
			{
				printf("export %s", tmp->name);
				if (tmp->var)
					printf("=\"%s\"", tmp->var);
				printf("\n");
			}
			tmp = tmp->next;
		}
		free(names[i]);
	}
	i = -1;
	free(names);
	free(order);
}
