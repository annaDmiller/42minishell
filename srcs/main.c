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

//    init_signal;
    all = init_all_struct();
    while (1)
    {
        all->prompt = print_prompt();
        all->line = readline(all->prompt);
        if (is_empty_line(all->line))
        {
            add_history(all->line);
        //parse_line(all->line);
        //free_lst(all->lst_cmd);
        }
        free (all->line);
        free(all->prompt);
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
    return (ret);
}
