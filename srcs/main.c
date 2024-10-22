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

volatile int    g_sig;

static t_all    *init_all_struct(void);

// int main(int argc, char **argv, char **envp)
// {
//     t_all   *all;
//     char    *prompt;
//     t_msh	msh;

//     g_sig = 0;
// //    init_signal;
// 	everyinit(&msh, envp);
//     while (1)
//     {
//         all = init_all_struct();
//         prompt = print_prompt(all);
//         all->line = readline(prompt);
//         free(prompt);
//         if (is_empty_line(all->line))
//         {
//             add_history(all->line);
//             //validate_line(all);
//             parse_line(all);
// 	    minishell(all, &msh);
//             //execute
//         }
//         free_all_struct(all);
//         rl_on_new_line();
//     }
//     rl_clear_history();
//     	(void)argc;
// 	(void)argv;
//     return (0);
// }

int	main(int argc, char **argv, char **envp)
{
	t_all   *all;
	t_msh	msh;

	g_sig = 0;
	everyinit(&msh, envp);
	// init_signal;
	while (1)
	{
		all = init_all_struct();
		all->line = readline("miniself > ");
		if (is_empty_line(all->line))
		{
			// printf("TESSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS\n");
			add_history(all->line);
			parse_line(all);
		// execute part //
			minishell(all, &msh);
			_var(all, &msh);
		}
		free_all_struct(all);
		if (msh.exit)
			break ;
		rl_on_new_line();
	}
	// rl_clear_history();
	clear_history();
	free(msh.pwd);
	freenv(msh.env);
	if (msh.exit)
		exit(msh.exit);
	(void)argc;
	(void)argv;
	return (0);
}

static t_all    *init_all_struct(void)
{
    t_all   *ret;

    ret = (t_all*) malloc(sizeof(t_all));
    if (!ret)
	error("init_all_struct: Malloc error\n", NULL);
    ret->exitstatus = 0;
    ret->line = NULL;
    ret->lst_cmd = NULL;
    ret->temp_l = NULL;
    ret->temp_for_free = NULL;
    ret->lst_env = NULL;
    return (ret);
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