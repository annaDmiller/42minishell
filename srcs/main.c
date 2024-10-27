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

static t_all	*init_all_struct(t_all *all, t_msh *msh);
static void process_line(t_all *all);

int main(int argc, char **argv, char **envp)
{
	t_all   *all;
	char    *line;
	t_msh   msh;

	g_sig = 0;
	all = NULL;
	everyinit(&msh, envp);
	init_signals(all);
	while (1)
	{
		// fprintf(stderr, "stdin // %d\t stdout // %d\n", STDIN_FILENO, STDOUT_FILENO);
		all = init_all_struct(all, &msh);
		// if (!msh._stdin_save && !msh._stdout_save)
		fprintf(stderr, "____________________________________________________\n\n");
		line = readline(PROMPT);
		if (!line)
			exit(1);
		all->line = line;
		if (is_empty_line(all->line))
			process_line(all);
		g_sig = 0;
		rl_on_new_line();
	}
	rl_clear_history();
	free_all_struct(all, 1);
	(void)argc;
	(void)argv;
	return (0);
}

static void process_line(t_all *all)
{
	int	check_line;

	check_line = 1;
	add_history(all->line);
	check_line = validate_line(all);
	if (!check_line || g_sig)
		return ;
	parse_line(all);
	if (g_sig)
		return ;
	minishell(all, all->msh);
	//     _var(all, all->msh);
	return ;
}

static t_all	*init_all_struct(t_all *all, t_msh *msh)
{
	if (!all)
	{
		all = (t_all *) malloc(sizeof(t_all));
		if (!all)
			error("init_all_struct: Malloc error\n", NULL);
		all->lst_env = NULL;
	all->line = NULL;
	}
    all->msh = msh;
    if (all->line)
    {
	free_all_struct(all, 0);
    }
	all->exitstatus = 0;
	all->line = NULL;
	all->lst_cmd = NULL;
	all->temp_l = NULL;
	all->temp_for_free = NULL;
	return (all);
}
