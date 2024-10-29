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
		if (!tmp->redir)
			fprintf(stderr, "!REDIR\n");
		else
		{
			if (tmp->name)
				fprintf(stderr, "\n\t%s\n\n", tmp->name);
			fprintf(stderr, "is_pipe // %c\n", tmp->redir->is_pipe);
			fprintf(stderr, "in_type // %c\n", tmp->redir->in_type);
			fprintf(stderr, "out_type // %c\n", tmp->redir->out_type);
			fprintf(stderr, "in_txt // %s\n", tmp->redir->in_txt);
			fprintf(stderr, "fd_infile // %d\n", tmp->redir->fd_infile);
			fprintf(stderr, "fd_outfile // %d\n", tmp->redir->fd_outfile);
			fprintf(stderr, "\n");
		}
		tmp = tmp->next;
	}
}

void	minishell(t_all *all, t_msh *msh)
{
	t_cmd	*cmd;
	pid_t		tpid;
	int		i;

	i = 0;
	cmd = all->lst_cmd;
	// fprintf(stderr, "_________________________________\n\n");
	print_redir_param(cmd); // while (!tmp) to change if you want it to work
	if (!cmd || !cmd->name)
		return ;
	if (!cmd->prev && !cmd->next)
	{
		if (cmd->redir) //
			cmd->redir->pos = SOLO;
		_execmd(all, all->msh, cmd);
	}
	else
	{
		// fprintf(stderr, "__________________________PIPE__________________________\n\n");
		tpipe(all, msh, cmd);
	}
	test(0);
	(void)i;
	(void)msh;
	(void)tpid;
}

	