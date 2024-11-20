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
#include "../../includes/minishell.h"

// NOT WORKING
// oldwork =en
static	int	*set_order(t_msh *msh, int length, int i);
static	char	**fill_names(t_msh *msh, int *order);
static	int	invalid_name(char *n);

static	int	invalid_name(char *n)
{
	int	i;

	i = -1;
	if (!n || (!((n[0] >= 65 && n[0] <= 90) || (n[0] >= 97
					&& n[0] <= 122)) && n[0] != '_'))
		return (1);
	while (n[++i] && n[i] != '=')
	{
		if (n[i] == '@' || n[i] == '~' || n[i] == '-' || n[i] == '.'
			|| n[i] == '{' || n[i] == '}' || n[i] == '*' || n[i] == '#'
			|| n[i] == '!' || n[i] == '+' )
			return (1);
	}
	return (0);
}

int	export(t_msh *msh, t_args *argv)
{
	char	*n;

	if (!argv)
		export_no_opt(msh);
	while (argv)
	{
		n = setup_name(argv->arg);
		if (invalid_name(argv->arg))
		{
			printf("export: `%s': not a valid indentifier\n", argv->arg);
			msh->exit = 1;
		}
		else
		{
			if (env_retrieve_var(msh->env, n) && env_retrieve_var(msh->env, n)->var && env_var(argv->arg))
			{
				free(env_retrieve_var(msh->env, n)->var);
				env_retrieve_var(msh->env, n)->var = env_var(argv->arg);
			}
			else if (!env_retrieve_var(msh->env, n))
				export_def(msh, argv);
		}
		argv = argv->next;
		if (n)
			free(n);
	}
	return (1);
}

void	export_def(t_msh *msh, t_args *argv)
{
	t_env	*new;
	t_env	*head;
	int		index;

	if (!msh || !msh->env)
		return ;
	head = msh->env;
	index = msh->env->id;
	while (msh->env->next)
	{
		msh->env = msh->env->next;
		index = msh->env->id;
	}
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return ;
	msh->env->next = new;
	new->id = index + 1;
	new->name = env_varname(argv->arg);
	new->var = env_var(argv->arg);
	new->next = NULL;
	msh->env = head;
}

void	export_no_opt(t_msh *msh)
{
	t_env		*tmp;
	int			*order;
	int			length;
	int			i;

	i = -1;
	length = l_envsize(msh->env) - 1;
	order = set_order(msh, length, -1);
	while (order && ++i <= length)
	{
		tmp = msh->env;
		while (tmp)
		{
			if (tmp->id == order[i] && tmp->name && tstrcmp(tmp->name, "_"))
			{
				if (!tmp->var)
					printf("export %s\n", tmp->name);
				else
					printf("export %s=\"%s\"\n", tmp->name, tmp->var);
			}
			tmp = tmp->next;
		}
	}
	if (order)
		free(order);
}

static	int	*set_order(t_msh *msh, int length, int i)
{
	t_env		*tmp;
	char		**names;
	int			*order;
	int			d;
	int			r;

	i = -1;
	tmp = msh->env;
	order = malloc(sizeof(int) * (length + 1));
	names = fill_names(msh, order);
	if (!names)
		return (NULL);
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
	fsplit(names);
	return (order);
}

static	char	**fill_names(t_msh *msh, int *order)
{
	t_env	*tmp;
	char	**names;
	int		i;

	i = -1;
	if (!order)
		return (NULL);
	names = malloc(sizeof(char *) * ((l_envsize(msh->env) + 1)));
	if (!names)
	{
		free(order);
		return (NULL);
	}
	tmp = msh->env;
	while (tmp)
	{
		names[++i] = tstrdup(tmp->name);
		tmp = tmp->next;
	}
	names[++i] = NULL;
	return (names);
}
