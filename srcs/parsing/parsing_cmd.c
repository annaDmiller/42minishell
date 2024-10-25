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

void	parse_cmd(t_all *all, t_cmd *last)
{
	char	*str;
	char	*temp;
	char	*temp1;

	str = NULL;
	while (*(all->line) || str)
	{
		if (last->redir)
			if (last->redir->is_pipe == 'y')
				break ;
		process_str(all, last, &str);
		while (!is_white_space(*(all->line)) /*&& last->quote == 0*/
			&& *(all->line))
			all->line++;
		if (*all->line == '\0')
			break ;
		if (str)
		{
			temp = take_str(all, last);
			temp1 = str;
			str = ft_strjoin(temp1, temp);
			free(temp);
			free(temp1);
			if (!str)
				error("parse_cmd: Malloc error\n", all);
		}
		else
			str = take_str(all, last);
	}
	return ;
}

static char	*take_str(t_all *all, t_cmd *cmd)
{
	if (!cmd->redir && cmd->prev)
	{
		cmd->redir = (t_redir *) malloc(sizeof(t_redir));
		if (!cmd->redir)
			error("take_str: Malloc error\n", all);
		init_redir(cmd->redir);
	}
	if (cmd->prev)
		cmd->redir->is_pipe = 'y';
	if (*(all->line) == '$' && is_white_space(*(all->line + 1)))
		return (handle_dollar(all, 0));
	if (!is_quote(*(all->line)))
		return (handle_quotes(all, cmd, 0));
	if (!is_redir(*(all->line)))
		return (handle_redir(all, cmd));
	return (handle_word(all, 0));
}

static void	process_str(t_all *all, t_cmd *cmd, char **str)
{
	if (cmd->quote || !(*str) || is_white_space(*(all->line)))
		return ;
	if (!cmd->name)
		cmd->name = *str;
	else
		add_arg(all, cmd, str);
	*str = NULL;
	return ;
}