/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_before_parsing.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:52:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/20 21:52:10 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	char	*_expand_var_exists(t_all *all, char *str, int i);

// static	void	process_line(t_all *all, t_msh *msh, char **line)
// {
// 	int	check_line;

// 	check_line = 1;
// 	all->line = *line;
// 	check_line = validate_line(all);
// 	if (!check_line)
// 		return ;
// 	// if (_expand_line_length(all, *line) != tstrlen(*line))
// 		// all->line = expand_line(all, tstrdup(*line));
// 	add_history(all->line);
// 	parse_line(all);
// 	if (!all->line || g_sig)
// 		return ;
// 	minishell(all, msh);
// }

char	*expand_line(t_all *all, char *str)
{
	char	*line;
	char	*expand;
	int		i;
	int		length;
	int		d;
	int		e;

	i = 0;
	e = -1;
	length = _expand_line_length(all, str);
	line = malloc(sizeof(char) * (length + 1));
	if (!line)
	{
		free(str);
		return (NULL);
	}
	while (str[i])
	{
		if (str[i] == '$' && _expand_var_exists(all, str, i))
		{
			d = -1;
			expand = _expand_var_exists(all, str, i);
			while (expand && expand[++d])
				line[++e] = expand[d];
			if (expand)
				i += tstrlen(_expand_var_exists(all, str, i));
		}
		else
		{
			line[++e] = str[i];
			i++;
		}
	}
	line[++e] = '\0';
	free(str);
	return (line);
}

static	char	*_expand_var_exists(t_all *all, char *str, int i)
{
	char	*name;
	t_env	*node;
	int		r;
	int		d;

	r = 0;
	while (str[i + r] && str[i + r] != ' ')
		r++;
	name = malloc(sizeof(char) * (tstrlen(str) + 1));
	if (!name)
		return (NULL);
	d = -1;
	while (++d != r)
		name[d] = str[i + 1 + d];
	name[d] = '\0';
	node = env_retrieve_var(all->msh->env, name);
	if (name && node->var)
		free(name);
	return (node->var);
}

int	_expand_line_length(t_all *all, char *str)
{
	char	*name;
	int		i;
	int		r;
	int		d;
	int		expand_length;

	i = 0;
	r = 0;
	d = 0;
	expand_length = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			r = 0;
			while (str[i + r] && str[i + r] != ' ')
				r++;
			name = malloc(sizeof(char) * (1000));
			if (!name)
				return (0);
			d = -1;
			while (++d != r)
				name[d] = str[i + 1 + d];
			name[d] = '\0';
			if (name && env_retrieve_var(all->msh->env, name) && env_retrieve_var(all->msh->env, name)->var)
			{
				expand_length += tstrlen(env_retrieve_var(all->msh->env, name)->var) - r;
				free(name);
				i += r;
			}
			else
				i++;
		}
		else
			i++;
	}
	return (expand_length + i);
}


// static char	*add_env_var(t_all *all, t_cmd *cmd)
	// this function will never be used then
//change	// return (parse_env_val(all, &env_val, cmd), free(env_val), NULL);
//to		// return (env_val);