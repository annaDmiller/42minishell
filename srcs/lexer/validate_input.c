#include "../../includes/minishell.h"

static int  validate_quotes(t_all *all);
static int  validate_pipes(t_all *all);
static int validate_redir(t_all *all);
static int  check_redir_addr(t_all *all, int *ind);

int validate_line(t_all *all)
{
    int check_q;
    int check_r;
    int check_p;

    check_q = validate_quotes(all);
    check_r = validate_redir(all);
    check_p = validate_pipes(all);
    if (!check_p || !check_q || !check_r)
        ft_putstr_fd("Syntax error: ", 2);
    if (!check_p)
        return (ft_putstr_fd("unexpected token '|'\n", 2), 0);
    if (!check_r)
        return (ft_putstr_fd("incorrect redirection\n", 2), 0);
    if (!check_q)
        return (ft_putstr_fd("quotes not closed\n", 2), 0);
    return (1);
}

static int  validate_quotes(t_all *all)
{
    int     ind;
    char    car;

    ind = 0;
    car = 0;
    while (all->line[ind])
    {
        car = 0;
        while (all->line[ind] != '|' && all->line[ind])
        {
            if (all->line[ind] == car)
                car = 0;
            if (!is_quote(all->line[ind]) && !car)
                car = all->line[ind];
            ind++;
        }
        if (car)
            return (0);
        if (all->line[ind])
            ind++;
    }
    if (car)
        return (0);
    return (1);
}

static int  validate_pipes(t_all *all)
{
    int ind;

    ind = 0;
    while (all->line[ind])
    {
        if (all->line[ind] == '|')
        {
            ind++;
            while (!is_white_space(all->line[ind]) && all->line[ind])
                ind++;
            if (all->line[ind] == '|' || all->line[ind] == 0)
                return (0);
        }
        ind++;
    }
    return (1);
}

static int validate_redir(t_all *all)
{
    int     ind;
    int     check;

    ind = 0;
    while (all->line[ind])
    {
        if (all->line[ind] == '>')
        {
            if (all->line[++ind] == '>')
                ind++;
            check = check_redir_addr(all, &ind);
        }
        else if (all->line[ind] == '<')
        {
            if (all->line[++ind] == '<')
                ind++;
            check = check_redir_addr(all, &ind);
        }
        if (!check)
            return (check);
        ind++;
    }
    return (check);
}

static int  check_redir_addr(t_all *all, int *ind)
{
    while (!is_white_space(all->line[*ind]) && all->line[*ind])
        (*ind)++;
    if (all->line[*ind] == 0 || !is_redir(all->line[*ind]))
        return (0);
    return (1);
}
