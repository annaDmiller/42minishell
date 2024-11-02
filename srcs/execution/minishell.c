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

static	void	print_redir_param(t_cmd *cmd);

void	wgas(char *str, int ext)
{
	printf("%s\n", str);
	exit(ext);
}

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;

	cmd = all->lst_cmd;
	print_redir_param(cmd); // while (!tmp) to change if you want it to work
	if (!cmd || !cmd->name)
		return ;
	else if (!cmd->prev && !cmd->next)
	{
		_execmd(all, msh, cmd, SOLO);
		if (!tstrcmp(cmd->name, "exit") && msh->exit)
			return ;
	}
	else
		tpipe(all, msh, cmd);
	while (wait(NULL) != -1)
		continue;
	// waitpid(pid, msh->exit, )
}

static	void	print_redir_param(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (!tmp)
	{	
		if (!tmp->redir)
			printf("!REDIR\n");
		else
		{
			if (tmp->name)
				printf("\n\t%s\n\n", tmp->name);
			printf("is_pipe // %c\n", tmp->redir->is_pipe);
			printf("in_type // %c\n", tmp->redir->in_type);
			printf("out_type // %c\n", tmp->redir->out_type);
			printf("in_txt // %s\n", tmp->redir->in_txt);
			printf("fd_infile // %d\n", tmp->redir->fd_infile);
			printf("fd_outfile // %d\n", tmp->redir->fd_outfile);
			printf("\n");
		}
		tmp = tmp->next;
	}
}