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

static t_all	*init_all_struct(t_all *all);
static void process_line(t_all *all, t_msh *msh);

int main(int argc, char **argv, char **envp)
{
	char	*line;
	t_all	*all;
	t_msh	msh;
	//char	*prompt;

	g_sig = 0;
	everyinit(&msh, envp);
	(void)argc;
	(void)argv;
	g_sig = 0;
	all = NULL;
	manage_signals();
	while (1)
	{
		all = init_all_struct(all);
		// fprintf(stderr, "\n////////////		NOUVELLLE CMD ->prochaine \n\n");
		line = readline(PROMPT);
		if (!line)
			exit(1);
		if (all->line)
			all = init_all_struct(all);
		all->line = line;
		if (is_empty_line(all->line))
			process_line(all, &msh);
		g_sig = 0;
		rl_on_new_line();
	}
	rl_clear_history();
	free_all_struct(all, 1);
	return (0);
	}

static void process_line(t_all *all, t_msh *msh)
{
    int check_line;

    check_line = 1;
    add_history(all->line);
    check_line = validate_line(all);
    if (!check_line || g_sig)
        return ;
    parse_line(all);
    if (g_sig)
        return ;
    minishell(all, msh);
    _var(all, &msh);
    return ;
}

static t_all	*init_all_struct(t_all *all)
{
	if (!all)
	{
		all = (t_all *) malloc(sizeof(t_all));
		if (!all)
			error("init_all_struct: Malloc error\n", NULL);
		all->lst_env = NULL;
        all->line = NULL;
	}
    if (all->line)
        free_all_struct(all, 0);
	all->exitstatus = 0;
	all->line = NULL;
	all->lst_cmd = NULL;
	all->temp_l = NULL;
	all->temp_for_free = NULL;
	return (all);
}

	// printf("%s\n", all->line);
	// for (t_cmd *cmd = all->lst_cmd; cmd; cmd = cmd->next)
	// {
	//     printf("CMD name: %s\n", cmd->name);
	//     if (cmd->redir)
	//     {
	//         printf("Redir input: %i\n", cmd->redir->fd_infile);
	//         printf("%c\n", cmd->redir->in_type);
	//         if (cmd->redir->in_txt)
	//             printf("%s", cmd->redir->in_txt);
	//         printf("Redir output: %i\n", cmd->redir->fd_outfile);
	//         printf("%c\n", cmd->redir->out_type);
	//         printf("Redir pipe: %c\n", cmd->redir->is_pipe);
	//     }
	//     for (t_args *arg = cmd->argv; arg; arg = arg->next)
	//     {
	//         printf("CMD arg: %s\n", arg->arg);
	//     }
	// }
	// sleep(5);