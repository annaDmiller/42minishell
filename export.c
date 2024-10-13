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

void	export(t_msh *msh, t_args *argv)
{
	if (!argv)
		export_no_opt(msh);
	else
		export_def(msh, argv);
}

//	leaks sur env_varname(str) && env_var(str) ! le noeud cree n'est pas relie correctement a la list ?

/// @brief leaks sur env_varname(str) && env_var(str)
/// le noeud cree n'est pas relie correctement a la list ?
/// Reamenager avec t_args *argv en argument
/// if not a valid indentifier we still need to create the node 
void	export_def(t_msh *msh, t_args *argv)
{
	t_env	*head;
	t_env	*new;
	t_env	*var;
	char	*n;
	int		tmpid;
	int	i = 1;

	while (argv)
	{
		n = setup_name(argv->arg);
		var = env_retrieve_var(msh->env, n);
		if (var) // si la variable existe deja on modifie seulement son contenu
		{
			free(var->var);
			var->var = env_var(argv->arg);
		}
		else
		{
			if (!((n[0] >= 65 && n[0] <= 90) || (n[0] >= 97 && n[0] <= 122)) && n[0] != '_')
				printf("export: `%s': not a valid indentifier\n", argv->arg);
			else
			{
				head = msh->env;
				tmpid = msh->env->id;
				while (msh->env->next)
				{
					msh->env = msh->env->next;
					tmpid = msh->env->id;
				}
				new = (t_env *)malloc(sizeof(t_env));
				if (!new)
					return ; // handle error
				new->name = env_varname(argv->arg);
 				new->var = env_var(argv->arg);
				new->id = tmpid + 1;
				new->next = NULL;
				msh->env->next = new;
				msh->env = head;
			}
		}
		freestr(n);
		i++;
		argv = argv->next;
	}
}



// void	export_def(t_msh *msh, t_args *argv)
// {
// 	t_env	*head;
// 	t_env	*new;
// 	t_env	*var;
// 	char	*n;
// 	int		tmpid;


// 	if (!argv)
// 		return ;	
// 	n = setup_name(argv->arg);
// 	var = env_retrieve_var(msh->env, n);
// 	if (var) // si la variable existe deja on modifie seulement son contenu
// 	{
// 		free(var->var);
// 		var->var = env_var(argv->arg);
// 		return (freestr(n));
// 	}
// 	if (!((n[0] >= 65 && n[0] <= 90) || (n[0] >= 97 && n[0] <= 122)) && n[0] != '_')
// 	{
// 		printf("export: `%s': not a valid indentifier\n", argv->arg);
// 		return (freestr(n));
// 	}
// 	head = msh->env;
// 	tmpid = msh->env->id;
// 	while (msh->env->next)
// 	{
// 		msh->env = msh->env->next;
// 		tmpid = msh->env->id;
// 	}
// 	new = (t_env *)malloc(sizeof(t_env));
// 	if (!new)
// 		return (freestr(n)); // handle error
// 	new->name = env_varname(argv->arg);
//  	new->var = env_var(argv->arg);
// 	new->id = tmpid + 1;
// 	new->next = NULL;
// 	msh->env->next = new;
// 	msh->env = head;
// }

int	tstrcmp(char *str, char *cmp)
{
	int	i;

	i = -1;
	while (str[++i] || cmp[i])
		if (str[i] != cmp[i])
			return (str[i] - cmp[i]);
	return (0);
}
/// @brief ////////// PBLM le premier argument export n'est pas passe en revue quand yala boucle de tstrcmp
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
	while (++i < length)
	{
		d = 0;
		r = -1;
		while (++r <= length)
			if (tstrcmp(tmp->name, names[r]) > 0)
				d++;
		printf("%s \t\t\t\t //%d positon\n", tmp->name, d);
		order[d] = tmp->id;
		tmp = tmp->next;
	}
	printf("\n\n");
	i = -1;
	while (++i < length)
	{
		tmp = msh->env;
		while (tmp)
		{
			// if (tmp->id == order[i] + 1)
				// printf("export %s=\"%s\"\n", tmp->name, tmp->var);
			tmp = tmp->next;
		}
	}
	i = -1;
	while (++i <= length)
		free(names[i]);
	free(names);
	free(order);
}












////		SAVE BEFORE UPDATING WTH *argv

// void	export_def(t_msh *msh, t_args *argv)
// {
// 	t_env	*head;
// 	t_env	*new;
// 	t_env	*var;
// 	char	*n;
// 	int		tmpid;

// 	if (!argv)
// 		return ;	
// 	n = setup_name(argv->arg);
// 	var = env_retrieve_var(msh->env, n);
// 	if (var) // si la variable existe deja on modifie seulement son contenu
// 	{
// 		free(var->var);
// 		var->var = env_var(argv->arg);
// 		return (freestr(n));
// 	}
// 	if (!((n[0] >= 65 && n[0] <= 90) || (n[0] >= 97 && n[0] <= 122)) && n[0] != '_')
// 	{
// 		printf("export: `%s': not a valid indentifier\n", argv->arg);
// 		return (freestr(n));
// 	}
// 	head = msh->env;
// 	tmpid = msh->env->id;
// 	while (msh->env->next)
// 	{
// 		msh->env = msh->env->next;
// 		tmpid = msh->env->id;
// 	}
// 	new = (t_env *)malloc(sizeof(t_env));
// 	if (!new)
// 		return (freestr(n)); // handle error
// 	new->name = env_varname(argv->arg);
//  	new->var = env_var(argv->arg);
// 	new->id = tmpid + 1;
// 	new->next = NULL;
// 	msh->env->next = new;
// 	msh->env = head;
// }
