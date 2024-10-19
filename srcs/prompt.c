/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:15:45 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/06 20:15:46 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// static void    get_user_host(char **prompt, t_all *all);
// static char    *get_host(char *addr, t_all *all);
// static char *shorten_addr(char **path, t_all *all);

char    *print_prompt(t_all *all)
{
    char *prompt;
    // char path[PATH_MAX];
    // char *temp;
    // char    *sh_path;

    // get_user_host(&prompt, all);
    // getcwd(path, sizeof(path));
    // temp = &(path[0]);
    // sh_path = shorten_addr(&(temp), all);
    // temp = prompt;
    // prompt = ft_strjoin(temp, sh_path);
    // free(temp);
    // free(sh_path);
    // if (!prompt)
    //     error("print_prompt: Malloc error\n", all);
    // temp = prompt;
    // prompt = ft_strjoin(temp, "$ ");
    prompt = tstrdup("Miniself // ");
    // free(temp);
    if (!prompt)
        error("print_prompt: Malloc error\n", all);
    return (prompt);
}

// static void    get_user_host(char **prompt, t_all *all)
// {
//     char *username;
//     char *host;
//     char *temp;

//     username = getenv("USER");
//     host = get_host("/etc/hostname", all);
//     if (!username || !host)
//         exit(1);
//     *prompt = ft_strjoin(username, "@");
//     if (!(*prompt))
//         error("get_user_host: Malloc error\n", all);
//     temp = *prompt;
//     *prompt = ft_strjoin(temp, host);
//     free(temp);
//     free(host);
//     if (!(*prompt))
//         error("get_user_host: Malloc error\n", all);
//     temp = *prompt;
//     *prompt = ft_strjoin(temp, ":");
//     free(temp);
//     if (!(*prompt))
//         error("get_user_host: Malloc error\n", all);
//     return ;    
// }

// static char    *get_host(char *addr, t_all *all)
// {
//     int fd;
//     char    *host;

//     fd = open(addr, O_RDONLY);
//     if (fd == -1)
//         error("get_host: impossible to print prompt\n", all);
//     host = get_next_line(fd);
//     close(fd);
//     if (!host)
//         exit(1);
//     host[ft_strlen(host) - 1] = '\0';
//     return (host);
// }

// static char *shorten_addr(char **path, t_all *all)
// {
//     char    *new_path;
//     char    *addr_short;
//     char    *temp;

//     addr_short = ft_strnstr(*path, getenv("USER"), ft_strlen(*path));
//     if (!addr_short)
//         return (*path);
//     new_path = ft_strdup(addr_short + ft_strlen(getenv("USER")));
//     if (!new_path)
//         error("shorten_addr: Malloc error\n", all);
//     temp = new_path;
//     new_path = ft_strjoin("~", temp);
//     free(temp);
//     if (!new_path)
//         error("shorten_addr: Malloc error\n", all);
//     return (new_path);
// }
