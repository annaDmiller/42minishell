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
	while (!tmp)
	{	
		if (!tmp->redir)
			fprintf(stderr, "!REDIR\n");
		else
		{
			fprintf(stderr, "is_pipe // %c\n", tmp->redir->is_pipe);
			fprintf(stderr, "in_type // %c\n", tmp->redir->in_type);
			fprintf(stderr, "out_type // %c\n", tmp->redir->out_type);
			fprintf(stderr, "in_txt // %s\n", tmp->redir->in_txt);
			fprintf(stderr, "fd_infile // %d\n", tmp->redir->fd_infile);
			fprintf(stderr, "fd_outfile // %d\n", tmp->redir->fd_outfile);
			fprintf(stderr, "\n\n");
		}
		fprintf(stderr, "\t%s\n\n", tmp->name);
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
	if (!cmd->next)
	{
		// fprintf(stderr, "__________________________SINGLE__________________________\n\n");
		msh->_stdout_save = dup(STDOUT_FILENO); // save STDOUT
		if (cmd->redir && cmd->redir->out_type != '0')
			if (dup2(cmd->redir->fd_outfile, STDOUT_FILENO) == -1)
				return ;// handle error
		tpid = fork();
		if (tpid == -1)
			return ;// handle error
		if (tpid == 0)
			_execmd(msh, cmd);
		waitpid(tpid, NULL, 0);
		dup2(msh->_stdout_save, STDOUT_FILENO); // restore STDOUT
		close(msh->_stdout_save);
		// fprintf(stderr, "_________________                    ________________\n\n");
		// t_env	*tmp;
		// tmp = msh->env;
		// while (tmp)
		// {
		// 	fprintf(stderr, "%s\n", tmp->name);
		// 	tmp = tmp->next;
		// }
	}
	else
	{
		// fprintf(stderr, "__________________________PIPE__________________________\n\n");
		tpipe(msh, cmd);
	}
	test(0);
	(void)i;
	(void)msh;
	(void)tpid;
}

	