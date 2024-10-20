/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:27 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:28 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*add_tail(t_all *all, t_cmd *cmd, char **head, int in_dollar);
static void	check_ending(t_all *all, t_cmd *cmd);
static char	*handle_double_quotes(t_all *all, t_cmd *cmd, int in_dollar);
static char	*handle_single_quotes(t_all *all, t_cmd *cmd);

char	*handle_quotes(t_all *all, t_cmd *cmd, int in_dollar)
{
	if (*(all->line++) == '"')
		return (handle_double_quotes(all, cmd, in_dollar));
	return (handle_single_quotes(all, cmd));
}

static char	*handle_double_quotes(t_all *all, t_cmd *cmd, int in_dollar)
{
	char	*str;
	int		ind;

	ind = 0;
	cmd->quote = 2;
	while (all->line[ind])
	{
		if (all->line[ind] == '"')
			break ;
		if (all->line[ind] == '$' && !in_dollar)
			if (is_white_space(all->line[ind + 1]) && all->line[ind + 1] != '"')
				break ;
		ind++;
	}
	str = (char *) malloc(sizeof(char) * (ind + 1));
	if (!str)
		error("handle_doub_quotes: Malloc error\n", all);
	ft_strlcpy(str, all->line, ind + 1);
	all->line += ind;
	check_ending(all, cmd);
	if (cmd->quote)
		return (add_tail(all, cmd, &str, in_dollar));
	return (str);
}

static char	*handle_single_quotes(t_all *all, t_cmd *cmd)
{
	char	*str;
	int		ind;

	ind = 0;
	cmd->quote = 1;
	while (all->line[ind])
	{
		if (all->line[ind] == '\'')
			break ;
		ind++;
	}
	str = (char *) malloc(sizeof(char) * (ind + 1));
	if (!str)
		error("handle_sing_quotes: Malloc error\n", all);
	ft_strlcpy(str, all->line, ind + 1);
	cmd->quote = 0;
	all->line += ind + 1;
	return (str);
}

static void	check_ending(t_all *all, t_cmd *cmd)
{
	if (*(all->line) == '"')
	{
		cmd->quote = 0;
		all->line++;
	}
	return ;
}

static char	*add_tail(t_all *all, t_cmd *cmd, char **head, int in_dollar)
{
	char	*env_val;
	char	*tail;

	all->temp_for_free = *head;
	env_val = handle_dollar(all, '"');
	*head = ft_strjoin(all->temp_for_free, env_val);
	free(all->temp_for_free);
	free(env_val);
	all->temp_for_free = NULL;
	if (*head)
		error("handle_quotes: Malloc error\n", all);
	if (!(*(all->line)))
		return (*head);
	all->temp_for_free = *head;
	tail = handle_double_quotes(all, cmd, in_dollar);
	*head = ft_strjoin(all->temp_for_free, tail);
	free(tail);
	free(all->temp_for_free);
	all->temp_for_free = NULL;
	if (*head)
		error("handle_quotes: Malloc error\n", all);
	return (*head);
}
