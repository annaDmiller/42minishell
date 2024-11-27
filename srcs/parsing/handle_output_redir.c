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

static void	output_replace(t_all *all, t_cmd *cmd);
static void	output_append(t_all *all, t_cmd *cmd);

void	handle_output(t_all *all, t_cmd *cmd)
{
	all->line++;
	if (*(all->line) == '>')
		output_append(all, cmd);
	else
		output_replace(all, cmd);
	return ;
}

static void	output_append(t_all *all, t_cmd *cmd)
{
	char	*addr;

	all->line++;
	addr = read_addr(all, cmd);
	if (!addr)
		return (error("output reditect: syntax error", all, SIGINT));
	if (!ft_strncmp(addr, "/dev/stdout", 11))
	{
		if (cmd->redir->outfile)
			return (free(addr));
		cmd->redir->outfile = addr;
		cmd->redir->out_type = 'a';
		return ;
	}
	if (cmd->redir->outfile)
	{
		free(cmd->redir->outfile);
		cmd->redir->outfile = NULL;
	}
	cmd->redir->outfile = addr;
	cmd->redir->out_type = 'a';
	open_and_close(all, cmd, cmd->redir->out_type);
	return ;
}

static void	output_replace(t_all *all, t_cmd *cmd)
{
	char	*addr;

	addr = read_addr(all, cmd);
	if (!addr)
		return (error("output reditect: syntax error", all, SIGINT));
	if (!ft_strncmp(addr, "/dev/stdout", 11))
	{
		if (cmd->redir->outfile)
			return (free(addr));
		cmd->redir->outfile = addr;
		cmd->redir->out_type = 'r';
		return ;
	}
	if (cmd->redir->outfile)
	{
		free(cmd->redir->outfile);
		cmd->redir->outfile = NULL;
	}
	cmd->redir->outfile = addr;
	cmd->redir->out_type = 'r';
	open_and_close(all, cmd, cmd->redir->out_type);
	return ;
}
