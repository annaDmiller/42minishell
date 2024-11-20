/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:15:36 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/06 20:15:40 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

volatile int	g_sig;

static	void	process_line(t_all *all, t_msh *msh, char **line);

int	main(int argc, char **argv, char **envp)
{
	t_all	*all;
	char	*line;
	t_msh	msh;

	g_sig = 0;
	all = NULL;
	everyinit(&msh, envp, argc, argv);
	init_signals(all);
	while (!msh.have_to_exit)
	{
		line = readline(PROMPT);
		if (g_sig == 2)
			msh.exit = 130;
		g_sig = 0;
		all = init_all_struct(all, &msh);
		if (!line)
			break ;
		if (is_empty_line(line))
			process_line(all, &msh, &line);
		rl_on_new_line();
	}
	if (!line)
		printf("exit\n");
	free_exit(all, &msh, 1);
	return (msh.exit);
}

static	void	process_line(t_all *all, t_msh *msh, char **line)
{
	int	check_line;

	check_line = 1;
	all->line = *line;
	add_history(all->line);
	check_line = validate_line(all);
	if (!check_line)
		return ;
	parse_line(all);
	if (!all->line || g_sig)
		return ;
	minishell(all, msh);
	if (g_sig == 2)
		msh->exit = 130;
	unlink(".eof");
}

t_all	*init_all_struct(t_all *all, t_msh *msh)
{
	if (!all)
	{
		all = (t_all *) malloc(sizeof(t_all));
		if (!all)
			error("init_all_struct: Malloc error", NULL, SIGTERM);
		all->line = NULL;
	}
	all->msh = msh;
	if (all->line)
	{
		free_all_struct(all, 0);
	}
	all->line = NULL;
	all->err = 0;
	all->lst_cmd = NULL;
	all->temp_l = NULL;
	all->temp_for_free = NULL;
	all->msh->hdc_situation = 0;
	return (all);
}
