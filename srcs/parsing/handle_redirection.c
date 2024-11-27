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

char	*handle_redir(t_all *all, t_cmd *cmd)
{
	t_redir	*redir;

	if (!cmd->redir)
	{
		redir = (t_redir *) malloc(sizeof(t_redir));
		if (!redir)
			error("handle_redir: Malloc error", all, SIGTERM);
		init_redir(redir);
		cmd->redir = redir;
	}
	cmd->quote = 1;
	if (*(all->line) == '>')
		handle_output(all, cmd);
	if (*(all->line) == '<')
		handle_input(all, cmd);
	if (*(all->line) == '|')
		handle_pipe(all, cmd);
	cmd->quote = 0;
	return (NULL);
}

void	init_redir(t_redir *redir)
{
	redir->is_pipe = 'n';
	redir->infile = NULL;
	redir->outfile = NULL;
	redir->in_type = '0';
	redir->out_type = '0';
	redir->stdin_delim = NULL;
	redir->name_delim = NULL;
	return ;
}

static void	handle_pipe(t_all *all, t_cmd *cmd)
{
	all->line++;
	cmd->redir->is_pipe = 'y';
	return ;
}

char	*read_addr(t_all *all, t_cmd *cmd)
{
	char	*temp;
	char	*ret;

	all->temp_for_free = NULL;
	ret = NULL;
	while (!is_white_space(*(all->line)) && *(all->line))
		all->line++;
	while (is_white_space(*(all->line)) && *(all->line) && is_redir(*all->line))
	{
		if (*(all->line) == '$')
			all->temp_for_free = handle_dollar(all, cmd);
		else if (!is_quote(*(all->line)))
			all->temp_for_free = handle_quotes(all, cmd, 0);
		else
			all->temp_for_free = handle_word(all, 0, 0);
		temp = ret;
		ret = ft_strjoin(temp, all->temp_for_free);
		if (!ret)
			error("read_addr: Malloc error", all, SIGTERM);
		free(temp);
		free(all->temp_for_free);
		all->temp_for_free = NULL;
	}
	all->temp_for_free = NULL;
	return (ret);
}

void	open_and_close(t_cmd *cmd, char type)
{
	int	fd;

	fd = 0;
	if (type == 'a')
		fd = open(cmd->redir->outfile, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (type == 'r')
		fd = open(cmd->redir->outfile, O_TRUNC | O_WRONLY | O_CREAT, 0666);
	if (fd == -1)
		return (err_msg(cmd->redir->outfile, NULL, NULL), perror(cmd->redir->outfile));
	if (type == 'f')
		fd = open(cmd->redir->infile, O_RDONLY);
	if (fd == -1)
		return (err_msg(cmd->redir->infile, NULL, NULL), perror(cmd->redir->infile));
	close(fd);
	return ;
}
