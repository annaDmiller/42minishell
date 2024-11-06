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

//file handles all cases of quotes '' and ""
static char	*add_tail(t_all *all, t_cmd *cmd, char **head, int in_dollar);
static void	check_ending(t_all *all, t_cmd *cmd);
static char	*handle_double_quotes(t_all *all, t_cmd *cmd, int in_dollar);
static char	*handle_single_quotes(t_all *all, t_cmd *cmd);

//function devides logic into 2 cases: for '' quotes and "" quotes
char	*handle_quotes(t_all *all, t_cmd *cmd, int in_dollar)
{
	if (*(all->line++) == '"')
		return (handle_double_quotes(all, cmd, in_dollar));
	return (handle_single_quotes(all, cmd));
}

//function handles case of double quotes
//if we faces $ sign, it adds to the string the line before dollar
//after thet it checks, whether it reached another double quote. If it's not that it adds value on env var and the "tail"
//it finishes when another double quote is reached
//done by recursion
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

//function handles single quotes
//it takes the whole line after next single quote and returns it
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

//function checks whether it reached the end of quoting part
//if so, then we restore 0 for quote var
static void	check_ending(t_all *all, t_cmd *cmd)
{
	if (*(all->line) == '"')
	{
		cmd->quote = 0;
		all->line++;
	}
	return ;
}

//function is triggered when it's required to get the env var value
//it handles the dollar; the env var value is added to the existing string of quoting
//if it didn't reach the end of line, then it triggers another double_quote handler
//result of double_quote handler is added to the existing line and all together is returned
static char	*add_tail(t_all *all, t_cmd *cmd, char **head, int in_dollar)
{
	char	*env_val;
	char	*tail;

	all->temp_for_free = *head;
	env_val = handle_dollar(all, cmd);
	*head = ft_strjoin(all->temp_for_free, env_val);
	free(all->temp_for_free);
	if (env_val)
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
