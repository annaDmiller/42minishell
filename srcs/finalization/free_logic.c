/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_logic.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 17:55:48 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/13 17:55:49 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minishell.h"

void	free_all_struct(t_all *all, int is_clear_env)
{
	if (all->temp_for_free)
		free(all->temp_for_free);
	if (all->temp_l)
		free(all->temp_l);
	if (!all->temp_l && all->line)
	{
		free(all->line);
		all->line = NULL;
	}
	if (all->lst_cmd)
		free_cmd_struct(all->lst_cmd);
	if (all->lst_env && is_clear_env)
		free_env_struct(all->lst_env);
	if (is_clear_env)
	{
		free(all);
		all = NULL;
	}
	return ;
}

void	free_cmd_struct(t_cmd *lst_cmd)
{
	t_cmd	*cmd;
	t_cmd	*temp;

	cmd = lst_cmd;
	while (cmd)
	{
		if (cmd->redir)
			free_redir_struct(cmd->redir);
		if (cmd->argv)
			free_args(cmd->argv);
		temp = cmd->next;
		free(cmd);
		cmd = temp;
	}
	lst_cmd = NULL;
	return ;
}

void	free_redir_struct(t_redir *redir)
{
	if (redir->in_txt)
		free(redir->in_txt);
	if (redir->fd_infile > 0)
		close(redir->fd_infile);
	if (redir->fd_outfile > 0)
		close (redir->fd_outfile);
	free(redir);
	redir = NULL;
	return ;
}

void	free_env_struct(t_env *lst_env)
{
	t_env	*env;
	t_env	*temp;

	env = lst_env;
	while (env)
	{
		temp = env->next;
		free(env);
		env = temp;
	}
	lst_env = NULL;
	return ;
}

void	free_args(t_args *lst_arg)
{
	t_args	*arg;
	t_args	*temp;

	arg = lst_arg;
	while (arg)
	{
		if (arg->arg)
			free(arg->arg);
		temp = arg->next;
		free(arg);
		arg = temp;
	}
	lst_arg = NULL;
	return ;
}
