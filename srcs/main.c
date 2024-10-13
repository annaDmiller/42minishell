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

int main(int argc, char **argv, char **env)
{
    t_all   *all;
    char    *prompt;

    g_sig = 0;
//    init_signal;
    all = init_all_struct();
    while (1)
    {
        prompt = print_prompt();
        all->line = readline(prompt);
        free(prompt);
        if (is_empty_line(all->line))
        {
            add_history(all->line);
        //parse_line(all->line);
        //free_lst(all->lst_cmd);
        }
        free (all->line);
        //free_all(all);
        //rl_on_new_line();
    }
    rl_clear_history();
    free(all);
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
