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

static char	*add_env_var(t_all *all);

char	*handle_dollar(t_all *all, t_cmd *cmd)
{
	char	*exitstatus;

	all->line++;
	if (ft_isalpha(*(all->line)) || *all->line == '_')
		return (add_env_var(all));
	if (*all->line == '?')
	{
		all->line++;
		exitstatus = ft_itoa(all->msh->exit);
		if (!exitstatus)
			error("handle_dollar: ft_itoa error", all, SIGINT);
		return (exitstatus);
	}
	if (!is_quote(*(all->line)))
		return (handle_quotes(all, cmd, 1));
	all->line--;
	return (handle_word(all, 1, 0));
}

static char	*add_env_var(t_all *all)
{
	char	*env_val;
	char	*env_name;
	t_env	*tmp;
	int		len_name;

	len_name = 0;
	env_val = NULL;
	while (is_white_space(all->line[len_name]) && *all->line
		&& (ft_isalnum(all->line[len_name]) || *all->line == '_'))
		len_name++;
	env_name = (char *) malloc((len_name + 1) * sizeof(char));
	if (!env_name)
		error("handle_dollar: Malloc error", all, SIGTERM);
	ft_strlcpy(env_name, all->line, len_name + 1);
	tmp = env_retrieve_var(all->msh->env, env_name);
	if (tmp && tmp->var)
		env_val = ft_strdup(env_retrieve_var(all->msh->env, env_name)->var);
	if (env_name)
		free(env_name);
	all->line += len_name;
	if (!env_val)
		return (NULL);
	return (env_val);
}
