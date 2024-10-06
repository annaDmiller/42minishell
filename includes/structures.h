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

typedef struct s_cmd
{
    char            *name;
    char            **argv;
    char            redir;
    struct s_cmd    *next;
    struct s_cmd    *prev;
}               t_cmd;

typedef struct  s_all
{
    struct s_cmd    *fst_cmd; 
}               t_all;
#endif
