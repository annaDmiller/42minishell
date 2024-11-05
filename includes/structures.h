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

typedef	enum	pos // used to know whats the position of the current command
{
	START, //PIPE// 
	MID, //PIPE//
	END, //PIPE//
	SOLO // a cmd alone so no call to tpipe function
}		t_pos;

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

typedef	struct s_execve // used in function set_execve
{
	char	*path;
	char		**argv;
	char		**envp;
}		t_execve;

typedef struct s_redir
{
	char	is_pipe; //if y, then we need to use pipex logic for the next command; if n, no need for pipex; need to think whether it's required if no semicolon sign can be used
	char	in_type; //if s - reading from stdin and read lines will be copied as one line into args list; if f - reading from file, the fd_infile must be != -1; if 0 - then no input redirection
	char	out_type; //if 'a' - write appending; if 'r' - write by replacing; if '0' - no output redirection
	char	*in_txt; //text which is taken from stdinput (used if in_type == s)
	int		fd_infile; //file descriptor for input redirection (used if in_type == f)
	int		fd_outfile; //file descriptor for outpur redirection
	int		tfile; //temporary file to stock heredoc in it, unlink it after finished the cmd
	t_pos		pos;
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

typedef struct spt ///for my split
{
	const char	*str;
	char		**split;
	char		c;
	int			nb_words;
	int			indic;
	int			len;
	int			op;
	int			i;
}		t_split; ///for my split

typedef struct s_msh // the structure I worked with while doing builtins without your parsing part
{
	t_env		*env; // linked list that stock the environnement // must not be freed except if we quit our minishell or if we exit a child process
	t_execve	*data; // little structure that contains *path; **argv; **envp; for execve(path, argv, envp)
	char		*pwd; // updated in every cd call 
	int			pipe_fd[2]; // when multiple cmd i use pipe_fd to redirect output inside pipe // pipe(msh->pipe_fd)
	int			exit; // perpetually updated with last exit value of the last cmd executed
	int			have_to_exit; // if the cmd is exit then i put it to 1 and i exit with msh->exit
	int			_stdin_save; // with multiple cmd i dup2(STDIN_FILENO) inside msh->_stdin_save and restore STDIN_FILENO at the end 
}		t_msh;

typedef struct s_all
{
	struct s_msh	*msh;
	struct s_cmd	*lst_cmd;
	char			*line; //line of command; freed after parsing part
	char			*temp_l; //temporary copy of line; freed after parsing part
	char			*temp_for_free; //temporary copy of separate char to free in case of error; freed after utilisation
}		t_all;
#endif
