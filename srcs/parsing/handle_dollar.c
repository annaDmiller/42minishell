/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:09 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:10 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static char	*add_env_var(t_all *all, char car);

char	*handle_dollar(t_all *all, char car)
{
	char	*exitstatus;

	all->line++;
	if (!ft_isalnum(*(all->line)) && *(all->line))
	{
		if (*(all->line) != '?')
		{
			all->line++;
			return (NULL);
		}
		all->line++;
		exitstatus = ft_itoa(all->exitstatus);
		if (!exitstatus)
			error("handle_dollar: ft_itoa error\n", all);
		return (exitstatus);
	}
	else if (!ft_isalpha(*(all->line)) && *(all->line))
	{
		all->line++;
		return (NULL);
	}
	return (add_env_var(all, car));
}

static char	*add_env_var(t_all *all, char car)
{
	char	*env_val;
	char	*env_name;
	int		len_name;
	char	*ret;

	len_name = 0;
	while (is_white_space(all->line[len_name])
		&& all->line[len_name] != car && ft_isalnum(all->line[len_name]))
		len_name++;
	env_name = (char *) malloc((len_name + 1) * sizeof(char));
	if (!env_name)
		error("handle_dollar: Malloc error\n", all);
	ft_strlcpy(env_name, all->line, len_name + 1);
	env_val = getenv(env_name);
	free(env_name);
	all->line += len_name;
	if (!env_val)
		return (NULL);
	ret = (char *) malloc(sizeof(char) * (ft_strlen(env_val) + 1));
	if (!ret)
		error("hadnle_dollar: Malloc error\n", all);
	ft_strlcpy(ret, env_val, ft_strlen(env_val) + 1);
	return (ret);
}
