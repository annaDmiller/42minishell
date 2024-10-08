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

static void    get_user_host(char **prompt);
static char    *get_host(char *addr);
static char *shorten_addr(char **path);

char    *print_prompt(void)
{
    char *prompt;
    char path[PATH_MAX];
    char *temp;
    char    *sh_path;

    get_user_host(&prompt);
    getcwd(path, sizeof(path));
    temp = &(path[0]);
    sh_path = shorten_addr(&(temp));
    temp = prompt;
    prompt = ft_strjoin(temp, sh_path);
    free(temp);
    free(sh_path);
    temp = prompt;
    prompt = ft_strjoin(temp, "$ ");
    free(temp);
    return (prompt);
}

static void    get_user_host(char **prompt)
{
    char *username;
    char *host;
    char *temp;

    username = getenv("USER");
    host = get_host("/etc/hostname");
    if (!username || !host)
        exit(1);
    *prompt = ft_strjoin(username, "@");
    temp = *prompt;
    *prompt = ft_strjoin(temp, host);
    free(temp);
    temp = *prompt;
    *prompt = ft_strjoin(temp, ":");
    free(temp);
    free(host);
    return ;    
}

static char    *get_host(char *addr)
{
    int fd;
    char    *host;

    fd = open(addr, O_RDONLY);
    if (fd == -1)
        exit(1);
    host = get_next_line(fd);
    if (!host)
        exit(1);
    host[ft_strlen(host) - 1] = '\0';
    return (host);
}

static char *shorten_addr(char **path)
{
    char    *new_path;
    char    *addr_short;
    char    *temp;

    addr_short = ft_strnstr(*path, getenv("USER"), ft_strlen(*path));
    if (!addr_short)
        return (*path);
    new_path = ft_strdup(addr_short + ft_strlen(getenv("USER")));
    temp = new_path;
    new_path = ft_strjoin("~", temp);
    free(temp);
    return (new_path);
}
