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

typedef enum pos
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
	char	in_type;
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
	int				quote;
	int				has_to_be_executed;
}		t_cmd;

typedef struct s_msh
{
	t_env		*env;
	t_execve	*data;
	char		*pwd;
	int			pipe_fd[2];
	int			exit;
	int			builtin_exit;
	int			have_to_exit;
	int			_stdin_save;
}		t_msh;

typedef struct s_all
{
	struct s_msh	*msh;
	struct s_cmd	*lst_cmd;
	char			*line;
	char			*temp_l;
	char			*temp_for_free;
	int				hdc_situation;
}		t_all;
#endif
