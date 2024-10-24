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

/// @brief Display the environnement		variable=value
/// // //   if there is no value, it just print variable=""
/// @param t_env *env 
void	env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (tmp->var)
			fprintf(stderr, "%s=%s\n", tmp->name, tmp->var);
		tmp = tmp->next;
	}
}

char	*env_var(char *str)
{
	char	*var;
	int		i;
	int		d;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	d = tstrlen(str) - i;
	if (d == -1)
		return (NULL);
	var = (char *)malloc(sizeof(char) * d + 1);
	if (!var)
		return (NULL); // error handling
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
	while (str[i] && str[i] != '=') // i will equal length of the name variable without its content
		i++;
	name = malloc(sizeof(char) * i + 1);
	if (!name)
		return (NULL); // error handling
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
		if (!tmp->name[i] && !str[i]) // if we arrived at the end without breaking before, words are the same
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
