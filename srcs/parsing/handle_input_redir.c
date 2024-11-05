/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:15 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:16 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static int	read_from_stdin(t_all *all, t_cmd *cmd);
static int	input_from_stdin(t_all *all, t_cmd *cmd);
static int	input_from_file(t_all *all, t_cmd *cmd);
static char	*read_keyword(t_all *all, t_cmd *cmd);

void	handle_input(t_all *all, t_cmd *cmd)
{
	all->line++;
	if (*(all->line) == '<')
		input_from_stdin(all, cmd);
	else
		input_from_file(all, cmd);
	return ;
}

static int	input_from_stdin(t_all *all, t_cmd *cmd)
{
	char	*temp;

	all->line++;
	temp = read_keyword(all, cmd);
	if (cmd->redir->fd_infile > 0)
	{
		if (cmd->redir->fd_infile)
			close(cmd->redir->fd_infile);
		if (cmd->redir->in_txt)
			free(cmd->redir->in_txt);
		cmd->redir->in_txt = NULL;
	}
	all->temp_for_free = ft_strjoin(temp, "\n");
	free(temp);
	if (!all->temp_for_free)
		return (error("input_from_stdin: Malloc error\n", all), 1);
	read_from_stdin(all, cmd);
	free(all->temp_for_free);
	all->temp_for_free = NULL;
	cmd->redir->in_type = 's';
	// cmd->redir->fd_infile = 0;
	return (0);
}

static int	input_from_file(t_all *all, t_cmd *cmd)
{
	char	*addr;

	addr = read_addr(all, cmd);
	if (!addr)
		return (error("input_redir: syntax error\n", all), 1);
	if (cmd->redir->fd_infile > 0)
		close(cmd->redir->fd_infile);
	cmd->redir->fd_infile = open(addr, O_RDONLY);
	if (cmd->redir->fd_infile == -1)
		return (error("input_from_file: impossible to open file\n", all), 1);
	cmd->redir->in_type = 'f';
	free(addr);
	return (0);
}

static int	read_from_stdin(t_all *all, t_cmd *cmd)
{
	char	*gnl;
	char	*temp;
	size_t	len_key;

	temp = NULL;
	cmd->redir->tfile = 0;
	len_key = ft_strlen(all->temp_for_free);
	putstr("> ");
	gnl = get_next_line(0);
	if (!gnl)
	{
		if (g_sig)
			return (1);
		else
			return (error("read_from_stdin: Malloc error\n", all), 1);
	}
	while (ft_strncmp(all->temp_for_free, gnl, len_key + 1) && !g_sig)
	{
		temp = cmd->redir->in_txt;
		cmd->redir->in_txt = ft_strjoin(temp, gnl);
		free(temp);
		free(gnl);
		if (!cmd->redir->in_txt)
			return (error("read_from_stdin: Malloc error\n", all), 1);
		putstr("> ");
		gnl = get_next_line(0);
	}
	if (cmd->redir->in_txt)
	{
		// str = 
		cmd->redir->tfile = open(".eof", O_WRONLY | O_TRUNC | O_CREAT, 0666);
		ft_putstr_fd(cmd->redir->in_txt, cmd->redir->tfile);
		close(cmd->redir->tfile);
	}
	free(gnl);
	return (0);
}

static char	*read_keyword(t_all *all, t_cmd *cmd)
{
	char	*temp;
	char	*ret;

	all->temp_for_free = NULL;
	ret = NULL;
	while (!is_white_space(*(all->line)) && *(all->line))
		all->line++;
	if (!is_redir(*(all->line)))
		return (NULL);
	while (is_white_space(*(all->line)) && *(all->line))
	{
		if (!is_quote(*(all->line)))
			all->temp_for_free = handle_quotes(all, cmd, 1);
		else
			all->temp_for_free = handle_word(all, 1);
		temp = ret;
		ret = ft_strjoin(temp, all->temp_for_free);
		if (!ret)
			return (error("read_addr: Malloc error\n", all), NULL);
		free(temp);
		free(all->temp_for_free);
		all->temp_for_free = NULL;
	}
	all->temp_for_free = NULL;
	return (ret);
}
