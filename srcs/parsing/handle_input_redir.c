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

static int	input_from_file(t_all *all, t_cmd *cmd);

void	handle_input(t_all *all, t_cmd *cmd)
{
	all->line++;
	if (*(all->line) == '<')
		input_from_stdin(all, cmd);
	else
		input_from_file(all, cmd);
	return ;
}

static int	input_from_file(t_all *all, t_cmd *cmd)
{
	char	*addr;

	addr = read_addr(all, cmd);
	if (!addr)
		return (error("input_redir: syntax error\n", all, SIGINT), 1);
	if (cmd->redir->fd_infile > 0)
		close(cmd->redir->fd_infile);
	if (cmd->redir->in_txt)
	{
		free(cmd->redir->in_txt);
		cmd->redir->in_txt = NULL;
	}
	cmd->redir->fd_infile = open(addr, O_RDONLY);
	if (cmd->redir->fd_infile == -1)
	{
		cmd->has_to_be_executed = 0;
		fprintf(stderr, "%s: No such file or directory\n", addr);
	}
	else
		cmd->redir->in_type = 'f';
	free(addr);
	return (0);
}
