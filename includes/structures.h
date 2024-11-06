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

typedef enum pos // used to know whats the position of the current command
{
	START,
	MID,
	END,
	SOLO,
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

typedef struct s_execve
{
	char	**envp;
	char	**argv;
	char	*path;
}		t_execve;

typedef struct s_redir
{
	char	is_pipe;
	char	in_type; //if s - reading from stdin and read lines will be copied as one line into args list; if f - reading from file, the fd_infile must be != -1; if 0 - then no input redirection
	char	out_type;
	char	*in_txt;
	int		fd_infile;
	int		fd_outfile;
	t_pos	pos;
}		t_redir;

typedef struct s_cmd
{
	struct s_args	*argv;
	struct s_redir	*redir;
	struct s_cmd	*next;
	struct s_cmd	*prev;
	char			*name;
	int				quote; //whether we are in quoted sentence while processing the line
}		t_cmd;

typedef struct s_msh // the structure I worked with while doing builtins without your parsing part
{
	t_env		*env; // linked list that stock the environnement // must not be freed except if we quit our minishell or if we exit a child process
	t_execve	*data; // little structure that contains *path; **argv; **envp; for execve(path, argv, envp)
	char		*pwd; // updated in every cd call 
	int			pipe_fd[2]; // when multiple cmd i use pipe_fd to redirect output inside pipe // pipe(msh->pipe_fd)
	int			exit; // perpetually updated with last exit value of the last cmd executed
	int			builtin_exit; // depends on what happened inside the builtin
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
