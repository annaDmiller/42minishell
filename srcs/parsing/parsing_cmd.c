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
static void	add_str_to_cmd(t_all *all, t_cmd *cmd, char **str);
static void	process_str(t_all *all, t_cmd *cmd, char **str);

//function works with 1 cmd until line reaches the end or '|' symbol
//white spaces are skipped
//if the line reaches the end, function checks whether there a pipe logic
//then it adds 'y' value to is_pipe for last cmd as well
void	parse_cmd(t_all *all, t_cmd *last)
{
	char	*str;

	str = NULL;
	while (*(all->line) || str)
	{
		if (last->redir)
			if (last->redir->is_pipe == 'y')
				break ;
		add_str_to_cmd(all, last, &str);
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

//function contains logic to collect a string which then will be
//transferred to cmd.name or arguements of cmd
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
			error("process_str: Malloc error\n", all);
	}
	else
		*str = take_str(all, cmd);
	return ;
}

//function handles different cases and return str part by part
//cases: redirection, $ sign, quotes and ordinary word
//it also creates redir structure for the parts of pipe if there is no one
static char	*take_str(t_all *all, t_cmd *cmd)
{
	if (!cmd->redir && cmd->prev)
	{
		cmd->redir = (t_redir *) malloc(sizeof(t_redir));
		if (!cmd->redir)
			error("take_str: Malloc error\n", all);
		init_redir(cmd->redir);
	}
	if (*(all->line) == '$' && is_white_space(*(all->line + 1)))
		return (handle_dollar(all, cmd));
	if (!is_quote(*(all->line)))
		return (handle_quotes(all, cmd, 0));
	if (!is_redir(*(all->line)))
		return (handle_redir(all, cmd));
	return (handle_word(all, 0));
}

//function processes a passed string as adding it to cmd.name or cmd arguements
//if there are whitespaces or on the pointer, then we need to continue collecting string
//if string is empty or quote doesn't equal to 0, it continues collecting string
//if it's '|' symbol, then we add string to the arguement/name and move on
static void	add_str_to_cmd(t_all *all, t_cmd *cmd, char **str)
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
