/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:34 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:35 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static void	handle_pipe(t_all *all, t_cmd *cmd);

//function devides cases for different redirection symbols
//it also initializes the cmd->redir if it's not initialized yet
char	*handle_redir(t_all *all, t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd->redir)
	{
		redir = (t_redir *) malloc(sizeof(t_redir));
		if (!redir)
			error("handle_redir: Malloc error\n", all);
		init_redir(redir);
		cmd->redir = redir;
	}
	if (*(all->line) == '>')
		handle_output(all, cmd);
	if (*(all->line) == '<')
		handle_input(all, cmd);
	if (*(all->line) == '|')
		handle_pipe(all, cmd);
	return (NULL);
}

//function defines default values for all variables of redir structure
void	init_redir(t_redir *redir)
{
	redir->is_pipe = 'n';
	redir->fd_infile = -2;
	redir->fd_outfile = -2;
	redir->in_type = '0';
	redir->out_type = '0';
	redir->in_txt = NULL;
	redir->tfile = -2;
	return ;
}

//function handles pipes by just adding is_pipe = 'y' as indicator for pipes
static void	handle_pipe(t_all *all, t_cmd *cmd)
{
	all->line++;
	cmd->redir->is_pipe = 'y';
	return ;
}

//function is used by >, >> and < redirections to read the following address
//it handles the $ sign, quotes and a word
char	*read_addr(t_all *all, t_cmd *cmd)
{
	char	*temp;
	char	*ret;

	all->temp_for_free = NULL;
	ret = NULL;
	while (!is_white_space(*(all->line)) && *(all->line))
		all->line++;
	while (is_white_space(*(all->line)) && *(all->line))
	{
		if (*(all->line) == '$')
			all->temp_for_free = handle_dollar(all, cmd);
		else if (!is_quote(*(all->line)))
			all->temp_for_free = handle_quotes(all, cmd, 0);
		else
			all->temp_for_free = handle_word(all, 0);
		temp = ret;
		ret = ft_strjoin(temp, all->temp_for_free);
		if (!ret)
			error("read_addr: Malloc error\n", all);
		free(temp);
		free(all->temp_for_free);
		all->temp_for_free = NULL;
	}
	all->temp_for_free = NULL;
	return (ret);
}
