/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:45:03 by tespandj          #+#    #+#             */
/*   Updated: 2024/09/12 17:04:38 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/pipex.h"

void	putstrfd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

static void	f_exec(struct ppx *ppx, int d)
{
	if (d == 1 || d == 2)
	{
		if (d == 1 && ppx->cmd1[0])
			putstrfd(ppx->cmd1[0], 2);
		else if (d == 2 && ppx->cmd2[0])
			putstrfd(ppx->cmd2[0], 2);
		write(2, ": command not found\n", 20);
	}
	fsplit(ppx->cmd1);
	fsplit(ppx->cmd2);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	exit(22);
}

void	exe(struct ppx *ppx)
{
	int		tfd;
	char	*path;

	if (ppx->cmd1[0] == NULL)
		f_exec(ppx, 1);
	tfd = open(ppx->in, O_RDONLY);
	if (tfd == -1)
	{
		perror(ppx->in);
		f_exec(ppx, 0);
	}
	if (dup2(tfd, STDIN_FILENO) == -1)
		wgas("");
	close(tfd);
	if (dup2(ppx->fd[1], STDOUT_FILENO) == -1)
		wgas("");
	close(ppx->fd[1]);
	close(ppx->fd[0]);
	path = fpath(ppx->env, ppx->cmd1[0], -1);
	if (!path)
		f_exec(ppx, 1);
	if (execve(path, ppx->cmd1, ppx->env) == -1)
		f_exec(ppx, 0);
}

void	cute(struct ppx *ppx)
{
	int		tfd;
	char	*path;

	if (ppx->cmd2[0] == NULL)
		f_exec(ppx, 2);
	tfd = open(ppx->out, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (tfd == -1)
	{
		perror(ppx->out);
		f_exec(ppx, 0);
	}
	if (dup2(ppx->fd[0], STDIN_FILENO) == -1)
		wgas("");
	if (dup2(tfd, STDOUT_FILENO) == -1)
		wgas("");
	close(tfd);
	close(ppx->fd[0]);
	close(ppx->fd[1]);
	path = fpath(ppx->env, ppx->cmd2[0], -1);
	if (!path)
		f_exec(ppx, 2);
	if (execve(path, ppx->cmd2, ppx->env) == -1)
		f_exec(ppx, 0);
}
