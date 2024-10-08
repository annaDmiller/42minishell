/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tespandj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 15:31:44 by tespandj          #+#    #+#             */
/*   Updated: 2024/10/06 17:02:12 by tespandj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct ppx
{
	int			fd[2];
	pid_t		pid1;
	pid_t		pid2;
	char		**env;
	char		*path;
	char		**cmd1;
	char		**cmd2;
	char		*in;	
	char		*out;
}			t_ppx;

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
}			t_split;

void			pipex(struct ppx *ppx, char **argv, char *const*env);

void			everinit(struct ppx *ppx, char **argv, char **env);
void			wgas(char *str);
void			fsplit(char **str);
void			wegotasplituation(struct spt x);

int				tstrlen(char *str);
char			*tstrdup(char *src);
char			*fpath(char **env, char *cmd, int i);
char			*tjoin(char *str, char *add);
char			*first_path(char *str);

char			**split(char const *str, char c);

void			putstrfd(char *str, int fd);
void			exe(struct ppx *ppx);
void			cute(struct ppx *ppx);

#endif
