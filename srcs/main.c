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
    char    *prompt;
    char    *cmd_line;
    t_cmd   *lst_cmd;

//    init_signal;
    while (1)
    {
        prompt = print_prompt();
        cmd_line = readline(prompt);
        add_history(cmd_line);
        lst_cmd = parse_line(cmd_line);
        free (cmd_line);
        free(prompt);
        free_lst(lst_cmd);
        rl_on_new_line();
    }
    rl_clear_history();
    return (0);
}
