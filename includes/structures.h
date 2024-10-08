/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amelniko <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 20:16:19 by amelniko          #+#    #+#             */
/*   Updated: 2024/10/06 20:16:19 by amelniko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct s_redir
{
    int     pipe_fd[2];
    char    *in_file;
    char    **out_file;
    char    out_type;
    char    **err_file;
    char    err_type;
}           t_redir;


typedef struct s_cmd
{
    char            *name;
    char            **opts;
    char            **argv;
    struct s_redit  *redir;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}               t_cmd;

typedef struct  s_env
{
    struct s_env    *next;
    struct s_env    *prev;
}                   t_env;

typedef struct  s_all
{
    struct s_cmd    *lst_cmd;
    char            *prompt;
    char            *line;
//    struct s_env    *lst_env;
}               t_all;
#endif
