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

	cmd = all->lst_cmd;
	print_param(cmd);
	if (!cmd || !cmd->name)
		return ;
	else if (!cmd->prev && !cmd->next)
	{
		_execmd(all, msh, cmd, SOLO);
		if (!tstrcmp(cmd->name, "exit") && g_sig)
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
	t_args	*argv;
	int		i;

	tmp = cmd;
	while (tmp)
	{
		argv = cmd->argv;
		if (!tmp->redir)
			fprintf(stderr, "!REDIR\n");
		else
		{
			if (tmp->name)
				fprintf(stderr, "\n\t%s\n\n", tmp->name);
			fprintf(stderr, "is_pipe // %c\n", tmp->redir->is_pipe);
			fprintf(stderr, "in_type // %c\n", tmp->redir->in_type);
			fprintf(stderr, "out_type // %c\n", tmp->redir->out_type);
			fprintf(stderr, "in_txt :\n\n%s\n\n", tmp->redir->in_txt);
			fprintf(stderr, "fd_infile // %d\n", tmp->redir->fd_infile);
			fprintf(stderr, "fd_outfile // %d\n\n", tmp->redir->fd_outfile);
		}
		tmp = tmp->next;
	}
	(void)argv;
	(void)i;
	fprintf(stderr, "\n____________________________\n\n");
}

			// i = -1;
			// while (argv && argv->arg && ++i < 22)
			// {
			// 	fprintf(stderr, "argv[%d] // %s\n", i, argv->arg);
			// 	argv = argv->next;
			// }