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

int main(int argc, char **argv, char **env)
{
    t_all   *all;
    //char    *prompt;

    (void)argc;
    (void)argv;
    (void)env;
    g_sig = 0;
    all = NULL;
    manage_signals();
    while (1)
    {
        all = init_all_struct(all);
        //prompt = print_prompt(all);
        all->line = readline(PROMPT);
        //all->line = ft_strdup("cat << $TEST");
        //free(prompt);
        if (is_empty_line(all->line))
        {
            add_history(all->line);
            //validate_line(all);
            parse_line(all);
            //execute
        }
        printf("%s\n", all->line);
        for (t_cmd *cmd = all->lst_cmd; cmd; cmd = cmd->next)
        {
            printf("CMD name: %s\n", cmd->name);
            if (cmd->redir)
            {
                printf("Redir input: %i\n", cmd->redir->fd_infile);
                printf("%c\n", cmd->redir->in_type);
                if (cmd->redir->in_txt)
                    printf("%s", cmd->redir->in_txt);
                printf("Redir output: %i\n", cmd->redir->fd_outfile);
                printf("%c\n", cmd->redir->out_type);
                printf("Redir pipe: %c\n", cmd->redir->is_pipe);
            }
            for (t_args *arg = cmd->argv; arg; arg = arg->next)
            {
                printf("CMD arg: %s\n", arg->arg);
            }
        }
        //sleep(5);
        free_all_struct(all, 0);
        rl_on_new_line();
    }
    rl_clear_history();
    return (0);
}

static t_all	*init_all_struct(t_all *all)
{
	if (!all)
	{
		all = (t_all *) malloc(sizeof(t_all));
		if (!all)
			error("init_all_struct: Malloc error\n", NULL);
		all->lst_env = NULL;
	}
	all->exitstatus = 0;
	all->line = NULL;
	all->lst_cmd = NULL;
	all->temp_l = NULL;
	all->temp_for_free = NULL;
	return (all);
}
