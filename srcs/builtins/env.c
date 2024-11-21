/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:24 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:25 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

int	env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->name && tmp->var)
			printf("%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
	return (1);
}

char	*env_var(char *str)
{
	char	*var;
	int		i;
	int		d;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] != '=')
		return (NULL);
	i++;
	d = tstrlen(str) - i;
	if (d == -1)
		return (NULL);
	var = (char *)malloc(sizeof(char) * d + 1);
	if (!var)
		return (NULL);
	var[d] = '\0';
	while (--d >= 0)
		var[d] = str[d + i];
	return (var);
}

char	*env_varname(char *str)
{
	char	*name;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL);
	name[i] = '\0';
	while (--i >= 0)
		name[i] = str[i];
	return (name);
}

t_env	*env_retrieve_var(t_env *env, char *str)
{
	t_env	*tmp;
	int		i;

	tmp = env;
	if (!str)
		return (NULL);
	while (tmp)
	{
		i = -1;
		while (tmp->name[++i] && str[i])
			if (tmp->name[i] != str[i])
				break ;
		if (!tmp->name[i] && !str[i])
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
