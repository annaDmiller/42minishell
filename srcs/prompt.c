#include "../includes/minishell.h"

static void    get_user_host(char **prompt);
static char    *get_host(char *addr);

char    *print_prompt(void)
{
    char *prompt;
    char path[PATH_MAX];
    char *temp;

    get_user_host(&prompt);
    getcwd(path, sizeof(path));
    temp = prompt;
    prompt = ft_strjoin(temp, &(path[0]));
    free(temp);
    temp = prompt;
    prompt = ft_strjoin(temp, " ");
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