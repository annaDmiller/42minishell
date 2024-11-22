/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_from_stdin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 10:49:04 by amelniko          #+#    #+#             */
/*   Updated: 2024/11/14 10:49:45 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_keyword(t_all *all, t_cmd *cmd);
static void	add_nl_to_line(t_all *all, t_cmd *cmd);

int	input_from_stdin(t_all *all, t_cmd *cmd)
{
	all->line++;
	if (cmd->redir->fd_infile >= 0)
	{
		if (cmd->redir->fd_infile)
			close(cmd->redir->fd_infile);
		if (cmd->redir->stdin_delim)
			free(cmd->redir->stdin_delim);
		if (cmd->redir->name_delim)
			free(cmd->redir->name_delim);
		cmd->redir->stdin_delim = NULL;
		cmd->redir->name_delim = NULL;
	}
	cmd->redir->name_delim = read_keyword(all, cmd);
	if (read_from_stdin(all, cmd) == 1 && !g_sig)
	{
		ft_putstr_fd("Here-doc is ended with EOF: wanted '", 2);
		write(2, cmd->redir->name_delim, ft_strlen(cmd->redir->name_delim));
		ft_putstr_fd("'\n", 2);
	}
	hdc_writing(all, cmd);
	cmd->redir->in_type = 's';
	cmd->redir->fd_infile = '0';
	return (0);
}

int	read_from_stdin(t_all *all, t_cmd *cmd)
{
	char	*gnl;
	char	*temp;
	size_t	len_key;

	temp = NULL;
	len_key = ft_strlen(cmd->redir->name_delim);
	while (!g_sig)
	{
		gnl = readline("> ");
		if (!gnl || g_sig)
			return (free(gnl), 1);
		if (!ft_strncmp(cmd->redir->name_delim, gnl, len_key + 1))
			break ;
		temp = cmd->redir->stdin_delim;
		cmd->redir->stdin_delim = ft_strjoin(temp, gnl);
		free(temp);
		free(gnl);
		if (!cmd->redir->stdin_delim)
			return (error("read_from_stdin: Malloc error", all, SIGTERM), -1);
		add_nl_to_line(all, cmd);
		rl_on_new_line();
	}
	return (free(gnl), 0);
}

static char	*read_keyword(t_all *all, t_cmd *cmd)
{
	char	*temp;
	char	*ret;

	all->temp_for_free = NULL;
	ret = NULL;
	while (!is_white_space(*(all->line)) && *(all->line))
		all->line++;
	while (is_white_space(*(all->line)) && *(all->line) && is_redir(*all->line))
	{
		if (!is_quote(*(all->line)))
			all->temp_for_free = handle_quotes(all, cmd, 1);
		else
			all->temp_for_free = handle_word(all, 1, 0);
		temp = ret;
		ret = ft_strjoin(temp, all->temp_for_free);
		if (!ret)
			return (error("read_addr: Malloc error", all, SIGTERM), NULL);
		free(temp);
		free(all->temp_for_free);
		all->temp_for_free = NULL;
	}
	all->temp_for_free = NULL;
	return (ret);
}

int	hdc_writing(t_all *all, t_cmd *cmd)
{
	free(cmd->redir->name_delim);
	cmd->redir->name_delim = NULL;
	if (cmd->redir->fd_infile > 0)
		close(cmd->redir->fd_infile);
	cmd->redir->fd_infile = open(".eof", O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (cmd->redir->fd_infile == -1)
		return (error("temp_input: open error", all, SIGINT), 1);
	if (cmd->redir->stdin_delim)
		ft_putstr_fd(cmd->redir->stdin_delim, cmd->redir->fd_infile);
	close(cmd->redir->fd_infile);
	all->msh->hdc_situation = 1;
	return (0);
}

static void	add_nl_to_line(t_all *all, t_cmd *cmd)
{
	char	*temp;

	temp = cmd->redir->stdin_delim;
	cmd->redir->stdin_delim = ft_strjoin(temp, "\n");
	free(temp);
	if (!cmd->redir->stdin_delim)
		return (error("read_from_stdin: Malloc error", all, SIGTERM));
	return ;
}
