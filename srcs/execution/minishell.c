/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 16:51:07 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/11 00:53:24 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

static	void	print_param(t_cmd *cmd);

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;

	if (!all->lst_cmd)
		return ;
	cmd = all->lst_cmd;
	print_param(cmd);
	if (!cmd->prev && !cmd->next)
	{
		_execmd(all, msh, cmd, SOLO);
		if (cmd->name && !tstrcmp(cmd->name, "exit") && g_sig)
			return ;
	}
	else
	{
		msh->_stdin_save = dup(STDIN_FILENO);
		tpipe(all, msh, cmd);
		dup2(msh->_stdin_save, STDIN_FILENO);
		close(msh->_stdin_save);
	}
	while (wait(NULL) != -1)
		continue ;
}

static	void	print_param(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (!tmp->redir)
			fprintf(stderr, "!REDIR\n");
		else
		{
			if (tmp->name)
				fprintf(stderr, "\n\t%s\n\n", tmp->name);
			fprintf(stderr, "is_pipe // %c\n", tmp->redir->is_pipe);
			fprintf(stderr, "in_type // %c\n", tmp->redir->in_type);
			fprintf(stderr, "out_type // %c\n", tmp->redir->out_type);
			fprintf(stderr, "fd_infile // %d\n", tmp->redir->fd_infile);
			fprintf(stderr, "fd_outfile // %d\n", tmp->redir->fd_outfile);
			fprintf(stderr, "has_to_be_executed // %d\n", tmp->has_to_be_executed);
			fprintf(stderr, "name_delim // %s\n", tmp->redir->name_delim);
			fprintf(stderr, "stdin_delim // \n\n%s\n", tmp->redir->stdin_delim);
		}
		tmp = tmp->next;
		fprintf(stderr, "\n____________________________\n\n");
	}
}
