/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 21:53:16 by tespandj          #+#    #+#             */
/*   Updated: 2024/11/20 21:53:19 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static void	proc_env_val(t_all *all, t_cmd *cmd, char **str);
static char	*take_env_word(t_all *all, t_cmd *cmd);

char	*parse_env_val(t_all *all, char **env_val, t_cmd *cmd)
{
	char	*temp;
	char	*str;

	temp = all->line;
	all->line = *env_val;
	all->temp_for_free = *env_val;
	str = NULL;
	while ((*(all->line) || str) && !g_sig)
	{
		add_str_to_cmd(all, cmd, &str);
		if (!(*(all->line)))
			break ;
		while (!is_white_space(*(all->line)) && *all->line)
				all->line++;
		proc_env_val(all, cmd, &str);
	}
	all->line = temp;
	all->temp_for_free = NULL;
	return (NULL);
}

static void	proc_env_val(t_all *all, t_cmd *cmd, char **str)
{
	char	*temp;
	char	*add_temp;

	temp = NULL;
	add_temp = NULL;
	if (*str)
	{
		temp = take_env_word(all, cmd);
		add_temp = *str;
		*str = ft_strjoin(add_temp, temp);
		free(temp);
		free(add_temp);
		if (!(*str))
			error("process_env_val: Malloc error", all, SIGTERM);
	}
	else
		*str = take_env_word(all, cmd);
	return ;
}

static char	*take_env_word(t_all *all, t_cmd *cmd)
{
	if (*(all->line) == '$' && is_white_space(*(all->line + 1)))
		return (handle_dollar(all, cmd));
	if (!is_quote(*(all->line)))
		return (handle_quotes(all, cmd, 0));
	return (handle_word(all, 0, 1));
}
