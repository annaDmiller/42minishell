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
	struct sigaction	*old_act_int;

	all->line++;
	if (*(all->line) == '<')
	{
		old_act_int = sigint_heredoc(all);
		input_from_stdin(all, cmd);
		restore_sigint_hdl(all, old_act_int);
	}
	else
		input_from_file(all, cmd);
	if (g_sig == SIGINT)
		all->msh->exit = 130;
	if (g_sig == SIGQUIT)
		all->msh->exit = 131;
	return ;
}

static int	input_from_file(t_all *all, t_cmd *cmd)
{
	char	*addr;

	addr = read_addr(all, cmd);
	if (!addr)
		return (error("input_redir: syntax error", all, SIGINT), 1);
	if (cmd->redir->infile)
	{
		free(cmd->redir->infile);
		cmd->redir->infile = NULL;
	}
	if (cmd->redir->stdin_delim)
	{
		free(cmd->redir->stdin_delim);
		cmd->redir->stdin_delim = NULL;
	}
	cmd->redir->infile = addr;
	cmd->redir->in_type = 'f';
	return (0);
}
