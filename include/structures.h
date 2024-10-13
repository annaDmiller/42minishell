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
# define STRUCTURES_H

typedef struct s_env
{
	struct s_env	*next;
	char			*var;
	char			*name;
	int				id;
	int				index;
}               t_env;

typedef struct s_msh
{
	t_env		*env;
	char		*pwd;
	char		**argv;
	int			argc;
        int                     exitstatus;

}		t_msh;

typedef struct s_redir
{
    int     pipe_fd[2]; //for pipex
    char    is_pipe; //if y, then we need to use pipex logic for the next command; if n, no need for pipex; need to think whether it's required if no semicolon sign can be used
    int     fd_infile; //file descriptor for input redirection
    char    in_type; //if s - reading from stdin and read lines will be copied as one line into args list; if f - reading from file, the fd_infile must be != -1; if 0 - then no input redirection
    int     fd_outfile; //file descriptor for outpur redirection
    char    out_type; //if 'a' - write appending; if 'r' - write by replacing; if '0' - no output redirection
}           t_redir;

typedef struct s_args
{
    char            *arg;
    struct s_args   *next;
    struct s_args   *prev;
}                   t_args;

typedef struct s_cmd
{
    char            *name; //the naming of the command, f.i. "echo" or "ls"
    struct s_args   *argv; // list of arguements
    int             quote; //whether we are in quoted sentence while processing the line
    struct s_redir  *redir; //list for redirection information; if it is NULL, then no redirection info, so just run the command
    struct s_cmd    *next;
    struct s_cmd    *prev;
}               t_cmd;

typedef struct  s_all
{
    struct s_cmd    *lst_cmd; //list of command
    char            *prompt; //maybe free before parsing and, therefore, remove from the structure?
    char            *line;
    char            *temp_l;
    int             exitstatus;
    // t_env           *env;
//    struct s_env    *lst_env;
}               t_all;

#endif