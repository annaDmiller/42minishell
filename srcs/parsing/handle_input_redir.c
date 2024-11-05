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

//functions devides cases into different functions for < and << redirections
void	handle_input(t_all *all, t_cmd *cmd)
{
	all->line++;
	if (*(all->line) == '<')
		input_from_stdin(all, cmd);
	else
		input_from_file(all, cmd);
	return ;
}

//function reads the address of the file to open and opens it for reading
//if there is already opened file for input, it closes the file descriptor (if only it's not 0)
//if there is already existing line taken from stdin, it frees it
static int	input_from_file(t_all *all, t_cmd *cmd)
{
	char	*addr;

	addr = read_addr(all, cmd);
	if (!addr)
		return (error("input_redir: syntax error\n", all), 1);
	if (cmd->redir->fd_infile > 0)
		close(cmd->redir->fd_infile);
	if (cmd->redir->in_txt)
	{
		free(cmd->redir->in_txt);
		cmd->redir->in_txt = NULL;
	}
	cmd->redir->fd_infile = open(addr, O_RDONLY);
	if (cmd->redir->fd_infile == -1)
		return (error("input_from_file: impossible to open file\n", all), 1);
	cmd->redir->in_type = 'f';
	free(addr);
	return (0);
}
