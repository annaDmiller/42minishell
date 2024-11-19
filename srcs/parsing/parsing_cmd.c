/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:42 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:43 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static char	*take_str(t_all *all, t_cmd *cmd);
static void	process_str(t_all *all, t_cmd *cmd, char **str);
static void	skip_cmd(t_all *all);

void	parse_cmd(t_all *all, t_cmd *last)
{
	char	*str;

	str = NULL;
	while ((*(all->line) || str) && !g_sig)
	{
		if (last->redir)
			if (last->redir->is_pipe == 'y')
				break ;
		add_str_to_cmd(all, last, &str);
		if (!last->has_to_be_executed)
			return (skip_cmd(all));
		while (!is_white_space(*(all->line)) && *(all->line))
			all->line++;
		if (*all->line == '\0')
		{
			if (last->prev)
				last->redir->is_pipe = 'y';
			break ;
		}
		process_str(all, last, &str);
	}
	return ;
}

static void	process_str(t_all *all, t_cmd *cmd, char **str)
{
	char	*temp;
	char	*add_temp;

	temp = NULL;
	add_temp = NULL;
	if (*str)
	{
		temp = take_str(all, cmd);
		add_temp = *str;
		*str = ft_strjoin(add_temp, temp);
		free(temp);
		free(add_temp);
		if (!(*str))
			error("process_str: Malloc error", all, SIGTERM);
	}
	else
		*str = take_str(all, cmd);
	return ;
}

static char	*take_str(t_all *all, t_cmd *cmd)
{
	if (!cmd->redir && cmd->prev)
	{
		cmd->redir = (t_redir *) malloc(sizeof(t_redir));
		if (!cmd->redir)
			error("take_str: Malloc error", all, SIGTERM);
		init_redir(cmd->redir);
	}
	if (*(all->line) == '$' && is_white_space(*(all->line + 1)))
		return (handle_dollar(all, cmd));
	if (!is_quote(*(all->line)))
		return (handle_quotes(all, cmd, 0));
	if (!is_redir(*(all->line)))
		return (handle_redir(all, cmd));
	return (handle_word(all, 0, 0));
}

void	add_str_to_cmd(t_all *all, t_cmd *cmd, char **str)
{
	if (cmd->quote || !(*str))
		return ;
	if (is_white_space(*(all->line)) && is_redir(*(all->line)))
		return ;
	if (!cmd->name)
		cmd->name = *str;
	else
		add_arg(all, cmd, str);
	*str = NULL;
	return ;
}

static void	skip_cmd(t_all *all)
{
	while (*(all->line) != '|' && *all->line)
		all->line++;
	if (*(all->line) == '|')
		all->line++;
	return ;
}
