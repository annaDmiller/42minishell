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
static	void	print_redir_param(t_redir *redir)
{
	t_redir	*tmp;

	tmp = redir;
	fprintf(stderr, "\n");
	if (!tmp)
		fprintf(stderr, "!REDIR\n");
	else
	{
		fprintf(stderr, "is_pipe // %c\n", tmp->is_pipe);
		fprintf(stderr, "in_type // %c\n", tmp->in_type);
		fprintf(stderr, "out_type // %c\n", tmp->out_type);
		fprintf(stderr, "in_txt // %s\n", tmp->in_txt);
		fprintf(stderr, "fd_infile // %d\n", tmp->fd_infile);
		fprintf(stderr, "fd_outfile // %d\n", tmp->fd_outfile);
	}
}

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;
	int		i;

	i = 0;
	cmd = all->lst_cmd;
	print_redir_param(cmd->redir);
	if (cmd->next)
	{
		fprintf(stderr, "_________________________________\n\n");
		print_redir_param(cmd->next->redir);
		fprintf(stderr, "\n\n");
	}
	if (!cmd->redir)
	{
		// fprintf(stderr, "__________________________SINGLE__________________________\n\n");
		_execmd(msh, cmd);
	}
	else if (cmd->redir && cmd->redir->is_pipe == 'y')
	{
		// fprintf(stderr, "__________________________PIPE__________________________\n\n");
		tpipe(msh, cmd);
		return ;
	}
	test(0);
	(void)i;
}
