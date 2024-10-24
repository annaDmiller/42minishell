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

typedef struct s_args
{
	char			*arg;
	struct s_args	*next;
	struct s_args	*prev;
}		t_args;

typedef struct s_env
{
	struct s_env	*next;
	char			*var;
	char			*name;
	int				id;
	int				index;
}		t_env;

typedef struct s_redir
{
	char	is_pipe; //if y, then we need to use pipex logic for the next command; if n, no need for pipex; need to think whether it's required if no semicolon sign can be used
	char	in_type; //if s - reading from stdin and read lines will be copied as one line into args list; if f - reading from file, the fd_infile must be != -1; if 0 - then no input redirection
	char	out_type; //if 'a' - write appending; if 'r' - write by replacing; if '0' - no output redirection
	char	*in_txt; //text which is taken from stdinput (used if in_type == s)
	int		pipe_fd[2]; //for pipex
	int		fd_infile; //file descriptor for input redirection (used if in_type == f)
	int		fd_outfile; //file descriptor for outpur redirection
	int		_tfd; // file descriptor to redirect output of cmd inside first and last cmd
}		t_redir;

typedef struct s_cmd
{
	struct s_args	*argv;
	struct s_redir	*redir; //list for redirection information; if it is NULL, then no redirection info, so just run the command
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*name;
	int				quote; //whether we are in quoted sentence while processing the line
}		t_cmd;

typedef struct spt
{
	const char	*str;
	char		**split;
	char		c;
	int			nb_words;
	int			indic;
	int			len;
	int			op;
	int			i;
}		t_split;

typedef struct s_msh
{
	t_env		*env;
	t_args		*l_args;
	char		*pwd;
	int			exit;
}		t_msh;

typedef struct s_all
{
	struct s_cmd	*lst_cmd;
	struct s_env	*lst_env;
	struct s_msh	*msh;
	char			*line; //line of command; freed after parsing part
	char			*temp_l; //temporary copy of line; freed after parsing part
	char			*temp_for_free; //temporary copy of separate char to free in case of error; freed after utilisation
	int				exitstatus; //exit status of the most recently executed foreground pipeline (needed for $? processing)
}		t_all;
#endif
