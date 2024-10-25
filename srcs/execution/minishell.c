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

static	void	test(int tt)
{
	int	i;

	i = -1;
	(void)i;
	(void)tt;
}

void	wgas(char *str, int ext)
{
	fprintf(stderr, "%s\n", str);
	exit(ext);
}
static	void	print_redir_param(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{	
		// if (!tmp->redir)
		// 	fprintf(stderr, "!REDIR\n");
		// else
		// {
		// 	fprintf(stderr, "is_pipe // %c\n", tmp->redir->is_pipe);
		// 	fprintf(stderr, "in_type // %c\n", tmp->redir->in_type);
		// 	fprintf(stderr, "out_type // %c\n", tmp->redir->out_type);
		// 	fprintf(stderr, "in_txt // %s\n", tmp->redir->in_txt);
		// 	fprintf(stderr, "fd_infile // %d\n", tmp->redir->fd_infile);
		// 	fprintf(stderr, "fd_outfile // %d\n", tmp->redir->fd_outfile);
		// 	fprintf(stderr, "\n\n");
		// }
		fprintf(stderr, "\t%s\n\n", tmp->name);
		tmp = tmp->next;
	}
}

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = all->lst_cmd;
	fprintf(stderr, "_________________________________\n\n");
	print_redir_param(cmd);
	if (!cmd)
	{
		return ;
	}
	if (!cmd->next)
	{
		// fprintf(stderr, "__________________________SINGLE__________________________\n\n");
		_execmd(msh, cmd);
	}
	else if (cmd->redir && cmd->redir->is_pipe == 'y')
	{
		// fprintf(stderr, "__________________________PIPE__________________________\n\n");
		tpipe(msh, cmd);
	}
	test(0);
	(void)i;
}

	// if (cmd)
	// {
	// 	// print_redir_param(cmd->next->redir);
	// 	fprintf(stderr, "\n\n");
	// 	if (cmd->next)
	// 	{
	// 		if (!cmd->next->redir) // init_redir(cmd->next->redir);
	// 		{
	// 			cmd->next->redir = malloc(sizeof(t_redir));
	// 			if (!cmd->next->redir)
	// 				fprintf(stderr, "MALLOC ERROR\n");
	// 			cmd->next->redir->is_pipe = 'n';
	// 			cmd->next->redir->fd_infile = -2;
	// 			cmd->next->redir->fd_outfile = -2;
	// 			cmd->next->redir->in_type = '0';
	// 			cmd->next->redir->out_type = '0';
	// 			cmd->next->redir->pipe_fd[0] = -2;
	// 			cmd->next->redir->pipe_fd[1] = -2;
	// 			cmd->next->redir->in_txt = NULL;
	// 		}
	// 	}
	// }