#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include "libft/libft.h"
#include "readline/readline.h"
#include "readline/history.h"

char    *handle_quotes(char **line);
char    *handle_double_quotes(char **line);
char    *handle_single_quotes(char **line);
static char *add_tail_until_finish(char **line, char **head);
static void check_ending(char **line);
static char *add_env_var(char **line, char car);
char    *handle_dollar(char **line, char car);
int  is_white_space(char car);

volatile int g_quote;

int main(void)
{

    char *ret;
    char *temp;
//    char *line = readline("");
    char    *line = (char *) malloc(sizeof(char) * (1 + strlen("$!TEST")));
    ft_strlcpy(line, "$!TEST", 1 + strlen("$!TEST"));
    temp = line;
    g_quote = 0;
    while (*line)
    {
        ret = NULL;
        if (*line == '"' || *line == '\'')
            ret = handle_quotes(&line);
        else if (*(line) == '$' && is_white_space(*(line + 1)) && *(line + 1))
            ret = handle_dollar(&line, 0);
        else
            line++;
        printf("%s\n", ret);
        free(ret);
    }
    free(temp);
    return (0);
}

char    *handle_quotes(char **line)
{
    if ((*(*line)++) == '"')
        return (handle_double_quotes(line));
    return (handle_single_quotes(line));
    }

char    *handle_double_quotes(char **line)
{
    char    *str;
    int     ind;
    int     len;

    ind =  0;
    g_quote = 2;
    len = 0;
    while ((*line)[ind])
    {
        if ((*line)[ind] == '"')
            break ;
        if ((*line)[ind] == '$')
            if (is_white_space((*line)[ind + 1]))
                break ;
        len++;
        ind++;
    }
    str = (char *) malloc(sizeof(char) * (len + 1));
    ft_strlcpy(str, *line, len + 1);
    (*line) += ind;
    check_ending(line);
    if (g_quote)
        return (add_tail_until_finish(line, &str));
    return (str);
}

char    *handle_single_quotes(char **line)
{
    char    *str;
    int     ind;
    int     len;
    char    *temp;
    char    *tail;

    ind =  0;
    g_quote = 1;
    len = 0;
    while ((*line)[ind])
    {
        if ((*line)[ind] == '\'')
            break ;
        len++;
        ind++;
    }
    str = (char *) malloc(sizeof(char) * (len + 1));
    strncpy(str, *line, len);
    g_quote = 0;
    *line += ind + 1;
    return (str);
}

static void check_ending(char **line)
{
    if (**line == '"')
    {
        g_quote = 0;
        (*line)++;
    }
    return ;
}

static char *add_tail_until_finish(char **line, char **head)
{
    char    *env_val;
    char    *tail;
    char    *temp;

    env_val = handle_dollar(line, '"');
    temp = *head;
    *head = ft_strjoin(temp, env_val);
    free(temp);
    free(env_val);
    check_ending(line);
    if (!(**line))
        return (*head);
    temp = *head;
    tail = handle_double_quotes(line);
    *head = ft_strjoin(temp, tail);
    free(tail);
    free(temp);
    temp = NULL;
    return (*head);
}


char    *handle_dollar(char **line, char car)
{
    char    *exitstatus;

    (*line)++;
    if (!isalnum(*(*line)) && **line)
    {
        if (*(*line) != '?')
        {
            (*line)++;
            return (NULL);
        }
        (*line)++;
        exitstatus = (char *) malloc(2 * sizeof(char));
        exitstatus[0] = '0';
        exitstatus[1] = 0;
        return (exitstatus);
    }
    else if (!isalpha(*(*line)) && **line)
    {
        (*line)++;
        return (NULL);
    }
    return (add_env_var(line, car));
}

static char *add_env_var(char **line, char car)
{
    char    *env_val;
    char    *env_name;
    int     len_name;
    char    *ret;

    len_name = 0;
    while (is_white_space((*line)[len_name]) && (*line)[len_name] && (*line)[len_name] != car)
        len_name++;
    env_name = (char *) malloc((len_name + 1) * sizeof(char));
    strncpy(env_name, (*line), len_name);
    env_val = getenv(env_name);
    (*line) += len_name;
    free(env_name);
    if (!env_val)
        return (NULL);
    ret = (char *) malloc(sizeof(char) * (strlen(env_val) + 1));
    strncpy(ret, env_val, strlen(env_val));
    return (ret);
}

int  is_white_space(char car)
{
    if (car == ' ' || car == '\v' || car == '\t' || car == '\r'
        || car == '\f' || car == '\n')
        return (0);
    return (1);
}