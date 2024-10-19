/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:54:06 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/14 19:54:09 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	int	free_env_var(t_env *var);

// bash-5.1$ env -i unset PATH
// env: ‘unset’: No such file or directory
// bash-5.1$
char	*setup_name(char *str)
{
	char    *name;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	name[i] = '\0';
	while (--i >= 0)
		name[i] = str[i];
	return (name);
}

/// @brief unset can take multiple arguments, and unset them one by one
/// it'll try to unset every argumenth if it exists // never will display an error message
/// @retval == 0 // All name operands were successfully unset.
/// @retval > 0  // At least one name could not be unset.
void    unset(t_msh *msh, t_args *argv)
{
	t_env	*save;
	t_env	*tmp;
	char		*name;

	while (argv)
	{
		tmp = msh->env;
		name = setup_name(argv->arg);
		if (env_retrieve_var(msh->env, name))
		{
			while (tmp->next != env_retrieve_var(msh->env, name))
				tmp = tmp->next;
			if (tmp->next->next)
			{
				save = tmp->next->next;
				free_env_var(tmp);
				tmp->next = save;
			}
			else if (free_env_var(tmp))
				tmp->next = NULL;
		}
		if (name)
			free(name);
		argv = argv->next;
	}
}

static	int	free_env_var(t_env *var)
{
	free(var->next->name);
	free(var->next->var);
	free(var->next);
	return (1);
}