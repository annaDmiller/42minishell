/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_output_redir.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:54:21 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:54:22 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static int	output_replace(t_all *all, t_cmd *cmd);
static int	output_append(t_all *all, t_cmd *cmd);

void	handle_output(t_all *all, t_cmd *cmd)
{
	all->line++;
	if (*(all->line) == '>')
		output_append(all, cmd);
	else
		output_replace(all, cmd);
	return ;
}

static int	output_append(t_all *all, t_cmd *cmd)
{
	char	*addr;

	all->line++;
	addr = read_addr(all, cmd);
	if (!addr)
		return (error("output reditect: syntax error", all, SIGINT), 1);
	if (!ft_strncmp(addr, "/dev/stdout", 11))
	{
		if (cmd->redir->fd_outfile != -2)
			return (0);
		cmd->redir->fd_outfile = 1;
		cmd->redir->out_type = 'a';
		return (0);
	}
	if (cmd->redir->fd_outfile != -2)
		close(cmd->redir->fd_outfile);
	cmd->redir->fd_outfile = open(addr, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (cmd->redir->fd_outfile == -1)
	{
		cmd->has_to_be_executed = 0;
		return (err_msg(NULL, addr, "couldnt retrieve/create\n"), free(addr), 1);
	}
	free(addr);
	cmd->redir->out_type = 'a';
	return (0);
}

static int	output_replace(t_all *all, t_cmd *cmd)
{
	char	*addr;

	addr = read_addr(all, cmd);
	if (!addr)
		return (error("output reditect: syntax error", all, SIGINT), 1);
	if (!ft_strncmp(addr, "/dev/stdout", 11))
	{
		if (cmd->redir->fd_outfile != -2)
			return (0);
		cmd->redir->fd_outfile = 1;
		cmd->redir->out_type = 'r';
		return (0);
	}
	if (cmd->redir->fd_outfile != -2)
		close(cmd->redir->fd_outfile);
	cmd->redir->fd_outfile = open(addr, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (cmd->redir->fd_outfile == -1)
	{
		cmd->has_to_be_executed = 0;
		return (err_msg(NULL, addr, "couldnt retrieve/create\n"), free(addr), 1);
	}
	free(addr);
	cmd->redir->out_type = 'r';
	return (0);
}
