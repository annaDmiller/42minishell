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

static void		process_line(t_all *all, t_msh *msh);
static t_all	*init_all_struct(t_all *all, t_msh *msh);

int	main(int argc, char **argv, char **envp)
{
	t_all	*all;
	char	*line;
	t_msh	msh;

	g_sig = 0;
	all = NULL;
	everyinit(&msh, envp);
	init_signals(all);
	while (!msh.have_to_exit)
	{
		all = init_all_struct(all, &msh);
		line = readline(PROMPT);
		if (!line)
			break ;
		all->line = line;
		if (is_empty_line(all->line))
			process_line(all, &msh);
		g_sig = 0;
		rl_on_new_line();
	}
	rl_clear_history();
	free_all_struct(all, 1);
	free(msh.pwd);
	free(msh.data);
	freenv(msh.env);
	(void)argc;
	(void)argv;
	return (msh.exit);
}

static	void	process_line(t_all *all, t_msh *msh)
{
	int	check_line;

	check_line = 1;
	add_history(all->line);
	check_line = validate_line(all);
	if (!check_line)
		return ;
	parse_line(all);
	minishell(all, msh);
	return ;
}

static t_all	*init_all_struct(t_all *all, t_msh *msh)
{
	if (!all)
	{
		all = (t_all *) malloc(sizeof(t_all));
		if (!all)
			error("init_all_struct: Malloc error\n", NULL);
		all->line = NULL;
	}
	all->msh = msh;
	if (all->line)
	{
		free_all_struct(all, 0);
	}
	all->line = NULL;
	all->lst_cmd = NULL;
	all->temp_l = NULL;
	all->temp_for_free = NULL;
	return (all);
}
